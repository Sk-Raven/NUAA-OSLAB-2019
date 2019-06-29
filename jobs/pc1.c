#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 4
int buffer1[CAPACITY];
int buffer2[CAPACITY];
int in1;
int out1;
int in2;
int out2;

int buffer_is_empty_1()
{
        return in1 == out1;
}

int buffer_is_full_1()
{
        return (in1 + 1) % CAPACITY == out1;
}

int get_item_1()
{
        int item;

            item = buffer1[out1];
                out1 = (out1 + 1) % CAPACITY;
                    return item;
}

void put_item_1(int item)
{
        buffer1[in1] = item;
            in1 = (in1 + 1) % CAPACITY;
}

int buffer_is_empty_2()
{
        return in2 == out2;
}

int buffer_is_full_2()
{
        return (in2 + 2) % CAPACITY == out2;
}

int get_item_2()
{
        int item;

            item = buffer2[out2];
                out2 = (out2 + 1) % CAPACITY;
                    return item;
}

void put_item_2(int item)
{
        buffer2[in2] = item;
            in2 = (in2 + 1) % CAPACITY;
}

pthread_mutex_t mutex_1;
pthread_cond_t wait_empty_buffer1;
pthread_cond_t wait_full_buffer1;
pthread_mutex_t mutex_2;
pthread_cond_t wait_empty_buffer2;
pthread_cond_t wait_full_buffer2;

#define ITEM_COUNT (CAPACITY * 2)

void *consume(void *arg)
{
        int i;
            int item;

                for (i = 0; i < ITEM_COUNT; i++) { 
                            pthread_mutex_lock(&mutex_2);
                                    while (buffer_is_empty_2())
                                                    pthread_cond_wait(&wait_full_buffer2, &mutex_2);

                                                            item = get_item_2(); 
                                                                    printf("consume item: %c\n", item); 

                                                                            pthread_cond_signal(&wait_empty_buffer2);
                                                                                    pthread_mutex_unlock(&mutex_2);
                                                                                        }
                                                                                            return NULL;
}

void *produce(void *arg)
{
        int i;
            int item;

                for (i = 0; i < ITEM_COUNT; i++) { 
                            pthread_mutex_lock(&mutex_1);
                                    while (buffer_is_full_1()) 
                                                    pthread_cond_wait(&wait_empty_buffer1, &mutex_1);

                                                            item = 'a' + i;
                                                                    put_item_1(item);
                                                                            printf("produce item: %c\n", item); 

                                                                                    pthread_cond_signal(&wait_full_buffer1);
                                                                                            pthread_mutex_unlock(&mutex_1);
                                                                                                }
                                                                                                    return NULL;
}

void *anaslye(void *arg)
{
        int i;
            int item;

                for (i = 0; i < ITEM_COUNT; i++) { 
                            pthread_mutex_lock(&mutex_1);
                                    pthread_mutex_lock(&mutex_2);
                                            while (buffer_is_full_2()) 
                                                            pthread_cond_wait(&wait_empty_buffer2, &mutex_2);
                                                                    while (buffer_is_empty_1()) 
                                                                                    pthread_cond_wait(&wait_full_buffer1, &mutex_1);
                                                                                            item = get_item_1(); 
                                                                                                    item -= 32;
                                                                                                            put_item_2(item);
                                                                                                                    printf("anaslye item: %c\n", item); 
                                                                                                                            
                                                                                                                                    
                                                                                                                                            pthread_cond_signal(&wait_full_buffer2);
                                                                                                                                                    pthread_mutex_unlock(&mutex_2);
                                                                                                                                                            pthread_cond_signal(&wait_empty_buffer1);        
                                                                                                                                                                    pthread_mutex_unlock(&mutex_1);
                                                                                                                                                                        }
                                                                                                                                                                            return NULL;
}

int main()
{ 
        pthread_t consumer_tid;
            pthread_t anaslye_tid;
                pthread_mutex_init(&mutex_1, NULL);
                    pthread_cond_init(&wait_empty_buffer1, NULL);
                        pthread_cond_init(&wait_full_buffer1, NULL);
                            pthread_mutex_init(&mutex_2, NULL);
                                pthread_cond_init(&wait_empty_buffer2, NULL);
                                    pthread_cond_init(&wait_full_buffer2, NULL);
                                        pthread_create(&anaslye_tid, NULL, anaslye, NULL);
                                            pthread_create(&consumer_tid, NULL, consume, NULL);
                                                
                                                    produce(NULL);
                                                        pthread_join(anaslye_tid, NULL);
                                                            pthread_join(consumer_tid, NULL);
                                                                return 0;
}
