#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

/*
 * todos os bits sendo: 1 -> broadcast/difusao      (se um quadro possui todos os bits 1 no campo de destino é aceito por todas as estações de rede)
 *                           multicast/multidifusao (apenas um grupo especifico pode receber)
 * 
 * uso do bit 46          -> serve para distinguir os endereços locais  (atribuidos dentro da rede e nao tem serventia fora dela)
 *                                                 de endereços globais (id unico globalmente)
 * 
 * Tipo                   -> especifica qual o protocolo/processo que deve receber o quadro
 * 
 * qual a funcao do transceptor?
 * problemas de se ter 0 bytes no campo de dados ? (quando o transceptor detecta uma colisao, o transceptor trunca o quadro atual
 *                                                  gerando bits perdidos e fragmentos de quadros)
 * 																								  isso gera uma necessidade de se ter pelo menos 64 bytes a partir do endereco de destino
 * 
 * ------------------------------------------------------------------------------------------------------------------------------------------
 * 
 * Ocorrencia de colisao ( uso do algoritmo de recuo binario exponencial, pg 221)
 * 														
 */

struct quadroET{
	int64_t preambulo;  //7 bytes   (identificador do quadro)
	int64_t destino;    //6 bytes   (bit de alta ordem: 0 -> endereços comuns
										  //						  							  1 -> endereços de grupos (permitem que diversas estações escutem um unico endereco)
	int64_t origem;     //6 bytes
	int16_t tipo;       //2 bytes
	char *data;         //24 - 1500 bytes
	char *Pad;          //0 - 46 bytes
	int32_t CheckSum;   //4 bytes   (verificador de erros, a partir do uso do algoritmo CRC, voltar no capitulo 3)
};

struct quadroET* quadro_new() {  
  struct quadroET* p = malloc(sizeof(struct quadroET)); 
	for(int i=1; i<=7; i+=2)
		p->preambulo |= (1ll<<i);

	p->data = malloc(sizeof(char) * 1500);
	p->Pad = malloc(sizeof(char) * 46);
  return p; 
}

struct meio{
	int8_t open;
	struct quadroET atual;
};

void Alocate(struct meio *MemShared){
	int id = shmget(IPC_PRIVATE, sizeof(MemShared), IPC_CREAT | 0666);
	if(id == -1)
		printf("Nao deu pra alocar\n"), exit(1);
	MemShared = (struct meio*) shmat(id, NULL, 0);
	if(MemShared == (struct meio*)-1)
		printf("Nao deu pra acoplar no bloco\n"), exit(1);
}


void Simulador(struct meio *process){
	//process->l = 0;
	while(1){
		
		while(!(process->open));
		
		process->open = 0;
		//~ process->D[process->head] = rand()%100;
		//~ process->head = (process->head + 1)%SIZE;
		process->open = 1;
	}
}


int main(){
	
	struct meio *MemShared = malloc(sizeof(struct meio));
	
	Alocate(MemShared);
	
	//~ waitpid(prod, NULL, 0);
	//~ waitpid(cons, NULL, 0);
	
	return 0;
}
