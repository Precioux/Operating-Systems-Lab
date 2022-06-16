#include <stdlib.h>
#include <time.h>
#include <stdio.h>
int main()
{
    srand(time(NULL));
    int counter=0;
    int hist[25]={0};
    int n;
    int a;
  for( a=0;a<500000;a++)
{
   counter=0;
   for(int i=0;i<12;i++)
   {
       n=rand()%100;
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
    printf("for %d times hist is :\n",a);
    for (int x=0;x<25;x++)
         printf("hist[%d]=%d\n",x,hist[x]);
    return 0;
}
