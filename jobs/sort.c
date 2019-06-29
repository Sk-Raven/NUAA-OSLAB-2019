#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int *num;
void sortselect(int *num,int start,int end)
{
   int i,j;
   for( i=start;i<end;i++){
       
        for( j=i+1;i<end;j++)
        {
          int index=i;
          if(num[index]>num[j])
              index=j;
          
        
        if(index!=i)
        {
            int temp=num[i];
            num[j]=num[index];
            num[index]=temp;
         }
        }
}
return;
}
void* work(void *arg)
{
    sortselect(num,100,200);
}

int main()
{
     num=malloc(100*sizeof(int));
     pthread_t work_tid;
     pthread_create(&work_tid,NULL,work,NULL);
     sortselect(num,0,100);
     pthread_join(work_tid,NULL);
     return 0;
}
