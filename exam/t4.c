#include <stdio.h>
#include <pthread.h>
int temp=0;
pthread_mutex_t mutex;
pthread_cond_t wait_apple;
pthread_cond_t wait_orange;
pthread_cond_t full_apple;
pthread_cond_t full_orange;
void *father_entry(void *arg)
{
   while(1)
{   pthread_mutex_lock(&mutex);
    while(temp!=0)
        pthread_cond_wait(&wait_orange,&mutex);
    temp=1;
    puts("put apple");
    pthread_cond_broadcast(&full_apple);
    pthread_mutex_unlock(&mutex);
    sleep(1);
}
    return NULL;
}

void *mother_entry(void *arg)
{
    while(1)
    {
    pthread_mutex_lock(&mutex);
    while(temp!=0)
        pthread_cond_wait(&wait_apple,&mutex);
    temp=2;
    puts("put orange");
    pthread_cond_broadcast(&full_orange);
    pthread_mutex_unlock(&mutex);
    sleep(1);
    }
    return NULL;
}

void *son_entry(void *arg)
{
    while(1)
    {
    pthread_mutex_lock(&mutex);
    while(temp!=1)
        pthread_cond_wait(&full_apple,&mutex);

    temp=0;    
    puts("get apple");
    pthread_cond_broadcast(&wait_apple);
    pthread_mutex_unlock(&mutex);
    sleep(1);
    }
    return NULL;
}

void *daughter_entry(void *arg)
{
   while(1){
   pthread_mutex_lock(&mutex);
    while(temp!=2)
        pthread_cond_wait(&full_orange,&mutex);
    temp=0;
    puts("get orange");
    pthread_cond_broadcast(&wait_orange);
    pthread_mutex_unlock(&mutex);
    sleep(1);
   }
    return NULL;
}

int main()
{
    pthread_t father_thread;
    pthread_t mother_thread;
    pthread_t son_thread;
    pthread_t daughter_thread;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&wait_apple,NULL);
    pthread_cond_init(&wait_orange,NULL);
    pthread_cond_init(&full_apple,NULL);
    pthread_cond_init(&full_orange,NULL);
    temp=0;
    pthread_create(&father_thread, NULL, &father_entry, NULL);
    sleep(1);
    pthread_create(&mother_thread, NULL, &mother_entry, NULL);
    pthread_create(&son_thread, NULL, &son_entry, NULL);
    pthread_create(&daughter_thread, NULL, &daughter_entry, NULL);

    while (1);
    return 0;
}
