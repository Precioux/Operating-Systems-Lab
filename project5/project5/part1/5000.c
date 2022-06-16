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
  for( a=0;a<5000;a++)
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
    return 0;
}
