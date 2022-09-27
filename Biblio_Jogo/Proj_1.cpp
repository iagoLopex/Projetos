#include <bits/stdc++.h>

using namespace std;

class Ficha{
	
public:
	int jogador;
	string cor;
	int torre;
};

queue player[4];
Ficha arm[55];               //armazenar fixas
string alf = "AVRB";         //indexar pela ordem de prioridade
int J_cor[4]={-1,-1,-1,-1};  //indexo o jogador com a respectiva cor 


void Distribuir_Fichas(){
	
	for(int i=0; i<52; i++){
		player[ (arm[i].jogador)-1 ] = arm[i];
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
	
	Armazenar_Fichas(input);
	Distribuir_Fichas();
	
	
	
	
	
	
	//~ cout << "prioridade:\n";
	//~ for(int i=0; i<4; i++){ cout << alf[i] << " " << J_cor[i] << endl; }
	//~ cout << "fichas 1\n";
	//~ for(int i=0; i<12; i++){ cout << arm[i].jogador << " " << arm[i].cor << " " << arm[i].torre << endl; }

}
