#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h> 
#include <unistd.h>

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
 * 
 * 
 * ------------------------------------------------------------------------------------------------------------------------------------------
 * 
 * Ocorrencia de colisao ( uso do algoritmo de recuo binario exponencial, pg 221)
 * 														
 */


struct quadroET{
	int64_t preambulo; //7 bytes
	int64_t destino;   //6 bytes   (bit de alta ordem: 0 -> endereços comuns
										 //						  							   1 -> endereços de grupos (permitem que diversas estações escutem um unico endereco)
	int64_t origem;    //6 bytes
	int16_t tipo;      //2 bytes
	string data;       //0 - 1500 bytes
	string Pad;        //0 - 46 bytes
	int32_t CheckSum   //4 bytes   (verificador de erros, a partir do uso do algoritmo CRC, voltar no capitulo 3)
	
	
	quadroET(){
		for(int i=1; i<=7; i+=2)
			preambulo |= (1ll<<i);
		
	}
};

int main(){
	
	
}
	
