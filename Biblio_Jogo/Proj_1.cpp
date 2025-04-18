#include <iostream>
#include <sstream>
#include "Ficha.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

queue<Ficha>player[4];
stack<Ficha>pilha[6];

Ficha arm[55];               //armazenar fixas
string alf = "AVRB";         //indexar pela ordem de prioridade
int J_cor[4]={-1,-1,-1,-1};  //indexo o jogador com a respectiva cor 
string tabuleiro[8][8];

void Inicializar_Interface(){
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			tabuleiro[i][j]="000";
		}
	}
}

//              linha      coluna
void Interface(int size, int index, string atual){
	
	tabuleiro[size][index]=atual;
	
	for(int i=5; i>=0; i--){
		for(int j=0; j<6; j++){
			cout << tabuleiro[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void Start(){
	
	int next;     //guardo o index do proximo jogador
	int i=0;      //rodadas de cada jogador
	Ficha proxF;  //ficha da rodada
	int k;        //posicao da pilha em que deve ser inse
	int cont=0;   //contador de fichas no tabuleiro
	
	cout << endl;
	while(cont < 36){//enquanto todas as pilhas ainda tiverem espaco
		
		next = J_cor[ (i%4) ];
		next--;
		proxF = player[next].front();
		k = proxF.torre-1;
		
		cout << "Fixa da rodada: " << proxF.Com  << " " << next << " " << i << endl;
		
		if(proxF.cor != 'P'){//a ficha nao eh preta

			if(pilha[ k ].size() < 6){//consigo inserir a ficha
				
				Interface(pilha[ k ].size(), k, proxF.Com);
				pilha[ k ].push( proxF );//insiro a ficha no tabuleiro				
				player[next].pop();      //retiro a ficha da mao do jogador
				cont++;                  //somo a contagem de fichas no tabuleiro
				
			}
			else{//nao consigo inserir a ficha

				if(cont<36){//ainda tem espaco
					
					int h=0;
					while(h<7 && pilha[ k ].size() == 6){//enquanto eu nao andei todas as pilhas e nao achei uma pilha vazia
						h++;
						k=(k+1)%6;
					}
					Interface(pilha[ k ].size(), k, proxF.Com);
					pilha[ k ].push( proxF );
					player[next].pop();
					cont++;
				}
			}
		}
		else{//ficha preta
			
			if(pilha[ k ].size()){  	//tenho elemento na pilha, entao consigo remover
				
				Interface(pilha[ k ].size(), k, "000");
				pilha[k].pop();     	//retiro a ficha do topo da pilha				
				player[next].pop(); 	//retiro a ficha na mao do jogador
				cont--;             	//diminuo a quantidade de fichas presentes no tabuleiro
			}
			else{//nao consigo remover
				player[next].pop(); 	//apenas retiro a ficha da mao do jogador
			}
		}
		
		i++;
	}
}

void Distribuir_Fichas(){
	
	for(int i=0; i<52; i++){
		player[ (arm[i].jogador)-1 ].push( arm[i] ); //cada jogador do index de arm recebe sua ficha
	}
}

void Armazenar_Fichas(string input){
	
	//preparando para separar as fichas inseridas
	stringstream ss(input);
	string fic;
	
	//contador de fichas
	int k=0;
	
	//armazenando as fichas, para serem destinadas a cada jogador
	while(ss>>fic){
		
		Ficha f;
		f.jogador = fic[0]-48;
		f.cor = fic[1];
		f.torre = fic[2]-48;
		f.Com = fic;
		
		//guardo a ficha
		arm[k]=f;
		
		//guardo a ordem de prioridade dos jogadores em um "mapa";
		for(int i=0; i<4; i++){
			if(fic[1]!='P' && J_cor[i]==-1 && alf[i] == fic[1]){//jogador -> cor
				J_cor[i]=fic[0]-48; //guardo o index do jogador daquela cor
			}
		}
		k++;
	}
}

int main(){
	
	string input;
	getline(cin, input);
	
	
	
	Inicializar_Interface();
	Armazenar_Fichas(input);
	Distribuir_Fichas();
	
	Start();
	
	for(int i=0; i<4; i++){
		cout << "jogador: " << i+1 << endl;
		while(!player[i].empty()){
			cout << player[i].front().jogador << " " << player[i].front().cor << " " << player[i].front().torre << endl;
			player[i].pop();
		}
		cout << endl;
	}
	
	//~ cout << "prioridade:\n";
	//~ for(int i=0; i<4; i++){ cout << alf[i] << " " << J_cor[i] << endl; }
	//~ cout << "fichas 1\n";
	//~ for(int i=0; i<12; i++){ cout << arm[i].jogador << " " << arm[i].cor << " " << arm[i].torre << endl; }

}
