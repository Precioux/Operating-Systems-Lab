#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#define MAX_num 25

int *hist;
// Called for each child process
void call(void)
{
    for(int a=0;a<12500;a++)
{
   int counter=0;
   for(int i=0;i<12;i++)
   {
       int n=rand()%100;
       if(n>49)
       {
           counter++;
       }
       else{
	 if(n<49)
	     counter--;
	}
   }
   hist[counter+12]++;
 }
  
}
void printHistogram(int *hist){
 int i,j;
 for( i=0;i<25;i++){
  for(j=0;j<hist[i];j++){
       printf("*");}
  printf("\n");
		   }
}

int main(int argc, char **argv)
{

  srand(time(NULL));
  // Map space for shared array
  hist = mmap(0, MAX_num*sizeof(int), PROT_READ|PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (!hist) {
    perror("mmap failed");
    exit(1);
  }
  memset((void *)hist, 0, MAX_num*sizeof(int));
 int j;
  // Fork the processes
  for(j = 0; j < 4; j++)
  {
    if (fork() == 0)
    {
        // Child process - do your child stuff
        call();
      //  printf("Child Process is done\n");
        // then just quit
        exit(0);
    }
  }

  j = 1;
  while (wait(NULL) > 0)
  {
   // printf("%d child completed\n", j++);
  }

  // In parent now
  //printf("all children terminated. in parent now\n");
//  printHistogram(hist);

  return 0;
}
