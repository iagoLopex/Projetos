#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

struct meio{
	int open;
	int atual;
};

void Alocate(struct meio *MemShared){
	int id = shmget(IPC_PRIVATE, sizeof(MemShared), IPC_CREAT | 0666);
	if(id == -1)
		printf("Nao deu pra alocar\n");
	MemShared = (struct meio*) shmat(id, NULL, 0);
	if(MemShared ==  (struct meio*)-1)
		printf("Nao deu pra acoplar no bloco\n");
}

void simulate(struct meio *principal){
	srandom(getpid());
	while(1){
		while(!(principal->open));
		
		principal->open = 0;
		int write = random()%2;
		int timeSleep = random()%20;
		principal->atual = write;
		
		printf("id %d   atual %d\n\n", getpid(), principal->atual);
		if(write != principal->atual)
			printf("------------colisao---------------\n");
		
		principal->open = 1;
		
		sleep(timeSleep);
	}
}

int main(){
	
	struct meio *principal = malloc(sizeof(struct meio));
	Alocate(principal);
	principal->open=1;
	
	pid_t p = fork();
	
	if(p == 0){
		for(int i=1; i<=10; i++){
			fork();	
		}
		simulate(principal);
	}
	else{
		printf("pai\n");
	}
}

