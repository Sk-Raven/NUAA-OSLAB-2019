#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>


int main()
{
    int fds[20];
    int i;
    int sum=0;
    for(i=0;i<20;i++)
       {
           
           pipe(&fds[i*2]);
       }
    for (i = 0; i < 10; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int j=0;
            int p_sum=0;
            for(j=(i*10+1);j<=(i+1)*10;j++)
                p_sum+=j;
           
         //  printf("%d\n",p_sum);
           
           write(fds[i*2+1],&p_sum,sizeof(int));
           for(i=0;i<20;i++)
               close(fds[i]);
           exit(0);
        }
    }

    


    
    for (i = 0; i < 10; i++) {
        int result=0;
        read(fds[i*2],&result,sizeof(int));
        sum += result;
    }
    for( i =0; i<20;i++)
        close(fds[i]);

    printf("sum = %d\n", sum);
    return 0;
}
