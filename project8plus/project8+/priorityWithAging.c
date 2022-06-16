#include<stdio.h>
#include<stdlib.h>
typedef struct {
int pid;
int priority;
int burstTime;
} process;
int times=0;
int compare (const void * a, const void * b)
{

  process *pA = (process *)a;
  process *pB = (process *)b;

  return ( pB->priority - pA->priority );
}
void printer(process processes[],int n){
for(int i=0;i<n;i++)
{
  printf("%d                %d                %d\n",processes[i].pid,processes[i].burstTime,processes[i].priority);
}
}

int findQ(process processes[],int n){
int q=0;
for(int i=0;i<n;i++)
{
 q+=processes[i].burstTime;
}
q/=n;
return q;
}
void reduceAndChange(process processes[],int n, int q){
if(q==0)
  q=processes[0].burstTime;
if(processes[0].burstTime>q)
   processes[0].burstTime-=q;
else {
processes[0].burstTime=0;
processes[0].priority=-1;
times++;
}
for(int i=1;i<n;i++)
{
processes[i].priority+=1;
}
}
int main()
{
 int n;
 int quantumTime;
 printf("Enter number of processes: \n");
 scanf("%d",&n);
 process processes[n];
 for(int i=0;i<n;i++)
{
 printf("Enter priority of process %d : \n",i);
 scanf("%d",&processes[i].priority);
 printf("Enter burst time of process %d : \n",i);
 scanf("%d",&processes[i].burstTime);
 processes[i].pid=i+1;
}
while (times<n){
qsort(processes, n, sizeof(process), compare);
printf("Queue gonna be : \n");
printf("pid        burstTime        priority\n");   
printer(processes,n);
quantumTime=findQ(processes,n);
printf("Quantum time : %d\n",quantumTime);
reduceAndChange(processes,n,quantumTime);
}
printf("Done!!\n");

return 0;
}
