#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
double result1=0;
double result2=0;
void *work(void *arg)
{
    
    int i=201;
    
    double j;
    for(;i<401;i++)
    {
        j=i;
        if(i%2==0)
            result1-=1/(2*j-1);
        else
            result1+=1/(2*j-1);

    
    
    }
    return NULL;
    
}

double master()
{
    int i=1;
    
    double j;
    for(i;i<201;i++)
    {
        j=i;
        if(i%2==0)
            result2-=1/(2*j-1);
        else
            result2+=1/(2*j-1);
    
    
    }
    
}
int main()
{
       pthread_t work_tid;
    
       pthread_create(&work_tid,NULL,work,NULL);
       master();
       pthread_join(work_tid,NULL);
       
       printf("%f\n",(result1+result2)*4);
       return 0;
}
