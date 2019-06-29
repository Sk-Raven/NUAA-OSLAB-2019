#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
struct param
{
    int start;
    int end;
};

struct result
{
    double worker_output;
};

void *work(void *arg)
{
    struct param *temp=(struct param*)arg;
    int i;
    struct result *output;
    double r=0;
    double j;
    for(i=temp->start;i<=temp->end;i++)
    {
        j=i;
        if(i%2==0)
            r-=1/(2*j-1);
        else
            r+=1/(2*j-1);
    }
    output=malloc(sizeof(struct result));
    output->worker_output=r;
    return output;
    
}

/*double master()
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
    
}*/
int main()
{
       int i;
       pthread_t work_tid[100];
       struct param params[100];
       double sum;
       for(i=0;i<100;i++)
       {
           struct param *t;
           t=&params[i];
           t->start=i*200+1;
           t->end=(i+1)*200;
           pthread_create(&work_tid[i],NULL,work,t);
       }
       for(i=0;i<100;i++)
       {
           struct result *t1;

           pthread_join(work_tid[i],(void **)&t1);
           sum+=t1->worker_output;
           free(t1);
       }
       
       printf("%f\n",sum*4);
       return 0;
}
