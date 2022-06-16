#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,sizeof(int)*2,0666|IPC_CREAT);

	// shmat to attach to shared memory
 	int *inp = (int*) shmat(shmid,NULL,0);

        
	printf("Enter two numbers : \n");
	scanf("%d%d",&inp[0],&inp[1]);

	printf("Data written in memory: %d %d\n",inp[0],inp[1]);
	
	//detach from shared memory
	shmdt(inp);
	

	return 0;
}

