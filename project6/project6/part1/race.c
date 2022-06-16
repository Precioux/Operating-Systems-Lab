#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_t tid;
pthread_t writerthreads[100],readerthreads[100];

int count=1;

void *reader(void* param)
{
    printf("reader is inside\n");
    printf("count is %d\n",count);
    printf("Reader is leaving\n");
    return NULL;
}

void *writer(void* param)
{
    printf("Writer has entered\n");
    count++;
    printf("Count is increased to %d\n",count);
    printf("Writer is leaving\n");
    return NULL;
}

int main()
{
    int n2,i;
    n2=2;
    printf("\n");
    int n1[n2];
  int flag=0;
  while ( count !=9){
  printf("count is %d\n",count);
    for(i=0;i<n2;i++)
    {  
       pthread_create(&writerthreads[i],NULL,reader,NULL);
       pthread_create(&readerthreads[i],NULL,writer,NULL);
    }      
   for(i=0;i<n2;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }
}

}
