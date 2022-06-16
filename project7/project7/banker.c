#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
//threads:
pthread_t tid[NUMBER_OF_CUSTOMERS];
pthread_mutex_t lock;

bool isSafe(){
    printf("Safety checking...\n");
    int work[NUMBER_OF_RESOURCES];
    //work <= available 
    for(int i=0; i<NUMBER_OF_RESOURCES; i++){
        work[i] = available[i];
    }

    bool finish[NUMBER_OF_CUSTOMERS];
    for(int i=0; i<NUMBER_OF_CUSTOMERS; i++){
        finish[i] = false;
    }

    int customerCtr = 0;
    bool flagCan = true;
    bool flag = true;
    while(customerCtr<NUMBER_OF_CUSTOMERS){

        if(finish[customerCtr] == false){
            for(int j=0 ; j<NUMBER_OF_RESOURCES;j++){
                if(need[customerCtr][j]>work[j])
                    flagCan = false;
            }
            if(flagCan){
                for(int k=0 ; k<NUMBER_OF_RESOURCES; k++)
                    work[k] += allocation[customerCtr][k];
                finish[customerCtr] = true;
                customerCtr++;
                break;
            }
        }

        for(int i=0 ; i<NUMBER_OF_CUSTOMERS; i++){
            if(finish[i] == false){
                for(int j=0 ; j<NUMBER_OF_RESOURCES; j++){
                    if(work[j]>need[customerCtr][j])
                        flag = false;
                break;
                }
            }
        }

        if(flag==true)
            return false;
    }

    return true;
}

bool request_resources(int request[], int customer_num) {

    printf("Customer %d is Requesting Resources:\n", customer_num);
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d  ",request[i]);
    }

    printf("\nAvailable = ");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d  ", available[i]);
    }
   for(int i=0;i<NUMBER_OF_RESOURCES;i++){
     need[customer_num][i]=maximum[customer_num][i]-allocation[customer_num][i];
    }
    printf("\nNeed = ");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d  ", need[customer_num][i]);
    }
    printf("\n");

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        //first check 2 constraints:
        if (request[i] <= need[customer_num][i]) {
            printf("OK..Request is lesser than need\n");
            if(request[i] <= available[i]){
	        printf("OK..Request is lesser than available\n");
                if( isSafe() ){
                    printf("Safe! Request is granted!\n");

                    for(int j=0 ; j<NUMBER_OF_RESOURCES ; j++){
                        available[j] -= request[j];
                        allocation[customer_num][j] += request[j];
                        need[customer_num][j] -= request[j];
  		printf("for resource %d : available=%d allocation=%d need=%d\n",j,available[j], allocation[customer_num][j],need[customer_num][j]);

                    }
    		    
                    return true;
                }else{
                    printf("Not safe! Can't grant request!\n");
                    return false;
                }
            }else{
                printf("Request is more than available! ABORT!\n");
                return false;
            }
        }else{
            printf("Request is more than need! ABORT!\n");
            return false;
        }
    }
}
void set(void)
{
    for(int i=0;i<NUMBER_OF_RESOURCES;i++)
	available[i]=10;
}
bool request_resources_control(int request[],int customer_num){
    //CRITICAL SECTION //
    bool released = false;
    pthread_mutex_lock(&lock);
    printf("Request control section .. locking critical section\n");
    released=request_resources(request, customer_num);
    pthread_mutex_unlock(&lock);
    return released;
}

bool release_resources(int resource, int customer_num){
    //give back resources:
        available[resource] =  available[resource]+ allocation[customer_num][resource];
        printf("available for %d is %d\n",resource,available[resource]);
    return true;
}
void release_resources_control(int customer_num){
    bool resualt=false;
    printf("Releasing resources...\n");
    pthread_mutex_lock(&lock);
    for(int i=0;i<NUMBER_OF_RESOURCES;i++)
       resualt=release_resources(i,customer_num);
    pthread_mutex_unlock(&lock);
    printf("Thread %d finished execution \n",customer_num);
}

void* getResources(void *arg){
    for(int i=0;i<NUMBER_OF_RESOURCES;i++)
	available[i]=10;
    int customerNum = *(int *)arg;
    printf("trying to get resources..\n");
    //a random request
    int request_one[] = {1,0,1};     //prototype for a request
    int request_two[] = {2,1,6};     //prototype for a request
   int request_three[] = {4,2,1};     //prototype for a request
    printf("Asking for request 1..\n");
    while(request_resources_control(request_one,customerNum)==false)
{
	printf("Waiting for accepting request1..\n");
}
    printf("Asking for request 2..\n");
    while(request_resources_control(request_two,customerNum)==false)
{
	printf("Waiting for accepting request2..\n");
}
    printf("Asking for request 3..\n");
    while(request_resources_control(request_three,customerNum)==false)
{
	printf("Waiting for accepting request3..\n");
}
    release_resources_control(customerNum);
    return 0;
}



int main(int argc, char *argv[]) {
    //check input:
    if (argc < NUMBER_OF_RESOURCES + 1) {
        printf("not enough arguments!\n");
        exit(1);
    }

    //initialization of our data structures:
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] = strtol(argv[i + 1], NULL, 10);
       // printf("av[%d] is %d\n",i,available[i]);
        for (int j = 0; j < NUMBER_OF_CUSTOMERS; j++) {
            maximum[j][i] = available[i]; //maximum possible amount of resource that a user can request for
            allocation[j][i] = 0;//default
            need[j][i] =  available[i];//t first, need is same as max
            }
    }

    //create the threads:
    int pid[] = {0,1,2,3,4};
    for (int i=0; i<NUMBER_OF_CUSTOMERS ; i++){
        pthread_create(&(tid[i]),NULL,getResources,&pid[i]);
    }

    for (int i=0; i<NUMBER_OF_CUSTOMERS ; i++){
        pthread_join(tid[i],0);
    }

    printf("FINISH!");
    pthread_mutex_destroy(&lock);
    return 0;
}


