#include <stdio.h>
#include <pthread.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

struct params
{
    int start;
    int end;
};

struct result
{
   int sum;
 };

 void *compute(void *args)
 {
     struct params *param=(struct params*)args;
     int sum=0;
     int i;
     for(i=param->start;i<=param->end;i++)
         sum+=i;
     
     struct result *result=malloc(sizeof(struct result));
     result->sum=sum;
     return result;
     }

int parallel_add(int start, int end)
{
    int middle=(start+end)/2;
    struct params param[2];
    pthread_t worker[2];
    int sum=0;
    int i=0;
    struct result *result;
    struct params *p_param=param;
    p_param->start=start;
    p_param->end=middle;
    pthread_create(&worker[0],NULL,compute,p_param);
    p_param++;
    p_param->start=middle+1;
    p_param->end=end;
    pthread_create(&worker[1],NULL,compute,p_param);
    for(i=0;i<2;i++)
    
    {
        
        pthread_join(worker[i],(void**)&result);
        sum+=result->sum;
        free(result);
     }
     return sum;


}

int main()
{
    // 1+2+3 ... + 100 = 5050
    printf("sum = %d\n", parallel_add(1, 101));
    return 0;
}
