#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
   int pid;
   int fd[2];
   int file;
   
   char buf[32];
   pipe(fd);
   pid=fork();
   if(pid==0)
   {
     dup2(fd[1],1);
     close(fd[0]);
     close(fd[1]);
     execlp("cat","cat","/etc/passwd",NULL);
     exit(0);
     
      
   }
   file=open("log.txt",O_CREAT|O_RDWR,666);
   dup2(fd[0],0);
   dup2(file,1);
   close(fd[0]);
   close(fd[1]);
   close(file);
   read(0,buf,sizeof(buf));
   execlp("wc","wc","-l",NULL);
   printf("%s",buf);
   return 0;
}
