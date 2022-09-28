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
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			tabuleiro[i][j]="000";
		}
	}
}

//              linha      coluna
void Interface(int size, int index, string atual){
	
	tabuleiro[size][index]=atual;
	
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
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
	int cont=1;   //contador de fichas no tabuleiro
	
	cout << endl;
	while(cont <= 16){//enquanto todas as pilhas ainda tiverem espaco
		
		next = J_cor[ (i%4) ];
		next--;
		proxF = player[next].front();
		k = proxF.torre-1;
		
		cout << "Fixa da rodada: " << proxF.Com  << " " << next << " " << i << endl;
		
		if(proxF.cor != 'P'){//a ficha nao eh preta
			
			//cout << "a ficha do jogador nao eh preta\n";
			if(pilha[ k ].size() < 6){//consigo inserir a ficha
				
				Interface(pilha[ k ].size(), k, proxF.Com);
				pilha[ k ].push( proxF );//insiro a ficha no tabuleiro				
				player[next].pop();      //retiro a ficha da mao do jogador
				
				//cout << player[next].front().jogador << " " << player[next].front().cor << " " << player[next].front().torre << endl;
				
				cont++;                  //somo a contagem de fichas no tabuleiro
				
			}
			else{//nao consigo inserir a ficha
				
			}
		}
		else{//ficha preta
			//cout << "a ficha do jogador eh preta\n";
			if(pilha[ k ].size()){  //tenho elemento na pilha, entao consigo remover
				
				Interface(pilha[ k ].size(), k, "000");
				pilha[k].pop();     //retiro a ficha do topo da pilha				
				player[next].pop(); //retiro a ficha na mao do jogador
				cont--;             //diminuo a quantidade de fichas presentes no tabuleiro
			}
			else{//nao consigo remover
				player[next].pop(); //apenas retiro a ficha da mao do jogador
			}
		}
		i++;
	}
	
	//teste
	//~ for(int i=0; i<4; i++){
		//~ cout << "jogador: " << i+1 << endl;
		//~ while(!player[i].empty()){
			//~ cout << player[i].front().jogador << " " << player[i].front().cor << " " << player[i].front().torre << endl;
			//~ player[i].pop();
		//~ }
	//~ }
	
}

void Distribuir_Fichas(){
	
	for(int i=0; i<16; i++){
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
		
		//guardo a ordem de prioridade dos jogadores em um mapa;
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

	//~ cout << "prioridade:\n";
	//~ for(int i=0; i<4; i++){ cout << alf[i] << " " << J_cor[i] << endl; }
	//~ cout << "fichas 1\n";
	//~ for(int i=0; i<12; i++){ cout << arm[i].jogador << " " << arm[i].cor << " " << arm[i].torre << endl; }

}
