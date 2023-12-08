#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

const int SIZE = 100;

using namespace std;

struct tree{
	int atual;
	int vet[4*SIZE];
	tree(){ atual=1; }
	void insert(int v){ vet[atual++]=v; }
};

struct obj{
	int head, tail, l;
	int D[SIZE];
	obj(){ head=tail=l=0; }
};

void Alocate(obj *MemShared){
	int id = shmget(IPC_PRIVATE, sizeof(MemShared), IPC_CREAT | 0666);
	if(id == -1)
		printf("Nao deu pra alocar\n"), exit(1);
	MemShared = (obj*) shmat(id, NULL, 0);
	if(MemShared == (obj*)-1)
		printf("Nao deu pra acoplar no bloco\n"), exit(1);
}

void produtor(obj *process, tree *Btree){
	process->l = 0;
	while(1){
		
		while(process->l);
		
		process->l = 1;
		process->D[process->head] = rand()%100;
		process->head = (process->head + 1)%SIZE;
		process->l = 0;
	}
}

void consumidor(obj *process, tree *Btree){
	while(1){
		
		while(process->l);
		
		process->l = 1;
		int v = process->D[process->tail];
		process->tail = (process->tail + 1)%SIZE;
		process->l = 0;
		
		Btree->insert(v);
	}
}

int main(){
	
	obj *MemShared = new obj;
	tree *Btree = new tree;
	Alocate(MemShared);
	srand(time(0));
	
	pid_t prod = fork();
	if(prod<0) //nao foi possivel duplicar
		exit(1);
	if(!prod)  //chamo o produtor
		produtor(MemShared, Btree), exit(0);
	
	pid_t cons = fork();
	if(cons<0) //nao foi possivel duplicar
		exit(1);
	if(!cons)  //chamo o produtor
		consumidor(MemShared, Btree), exit(0);
		
	waitpid(prod, NULL, 0);
	waitpid(cons, NULL, 0);
	
	return 0; 
}
