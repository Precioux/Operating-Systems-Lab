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
	int *data = (int*) shmat(shmid,NULL,0);

	printf("Data read from memory: %d %d\n",data[0],data[1]);
	printf("result = %d\n",data[0]+data[1]);
	
	//detach from shared memory
	shmdt(data);
	
	// destroy the shared memory
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}

