#include <bits/stdc++.h>

using namespace std;

void Armazenar_fichas(string);
void Distribuir_Fichas();
void Verificar_Jogada();
void Testar_Fim(int);

string alf = "AVRB";
string NextFicha;   //guardo a ficha da rodada
int i=0;          //orienta a prioridade da jogada ( azul -> vermelho -> roxo -> branco )
int cont=0;       //contador de pilhas cheias
int k;            //ando pilha por pilha, a partir da pilha do indice da ficha
bool Deu;         //verifico a jogada de cada rodada
bool ok  = false; //indica se todas as pilhas estao cheias, ou nao

map<char,int>mapa;
vector<string>vec;
vector<queue<string>>Jogador(4);
vector<stack<string>>Mesa(6);

void Armazenar_Fichas(string input){
	
	//preparando para separar as fichas inseridas
	stringstream ss(input);
	string ficha;
	
	//armazenando as fichas, para serem destinadas a cada jogador
	while(ss>>ficha){
		vec.push_back(ficha);
		
		//guardo a ordem de prioridade dos jogadores em um mapa;
		if(ficha[1]!='P' && mapa.find(ficha[1]) == mapa.end()){
			mapa[ficha[1]]=ficha[0]-48;
		}
	}
}

void Distribuir_Fichas(){
	
	string a,b,str;
	int x;
	//distribuindo as fichas para cada jogador
	for(int i=0; i<(int)vec.size(); i++){
		
		str="";                    
		a=vec[i][1]; b=vec[i][2];  
		str+=a; str+=b;            //pegando somente a ficha  
		
		x = (vec[i][0]-48)-1;      //a string que estou, na posicao do jogador
		                           //com o seu index em inteiro -1
		Jogador[ x ].push(str);
	}
}

void Verificar_Jogada(){
	
	int next;
	next = mapa[ alf[ (i%3) ] ];           //nessa posicao eu tenho o proximo jogador
	next--;
	
	Testar_Fim(next);
	
	if(cont == 6){//as pilhas estao todas cheias
		ok=true;
	}
	
	i++;  //vou para a proxima prioridade de cor
}

///  consertar o while dessa funcao ///////
//lembrar:
// antes de pegar o front daquele jogador eu tenho que verificar se ele possui fichas para jogar

void Testar_Fim(int next){
	
	cont=0;                                //contagem de pilhas cheias(reinicia a cada jogada)
	Deu=false;                             //verificar se a jogada deu certo
	NextFicha = Jogador[next].front();     //guardo a ficha a ser jogada
	k = (((Jogador[next].front())[1])-48); //inicializo k com a posicao que a ficha deve ir
	
	
	k--; //decrementar o k era um dos problemas
	
	
	while(cont<=6 && !Deu){
		
		//primeiramente, se a ficha for preta ja efetuo a jogada;
		if(NextFicha[0] == 'P'){
			
			if(Mesa[ (k%6) ].size() <= 6){//se tiver elemento
				
				Mesa[ (k%6) ].pop(); //retiro o topo da pilha
				Jogador[next].pop(); //retiro a ficha do jogador
			}
			
			Deu = true;
		}
		else{//verifico se a pilha tem espaco, se nao eu tento na proxima rodada do for (ou seja, a proxima pilha)
			
			if(Mesa[ (k%6) ].size() < 6){//tem espaco
				
				Mesa[ (k%6) ].push(NextFicha); //insiro a ficha
				cout << "inseri " << Mesa[ (k%6) ].top() << "    na posicao: "<< k+1 << endl;
				Jogador[next].pop();           //retiro a ficha do jogador
				Deu = true;
			}
		}
		cout << "k: "<< k << endl;
		
		
		k++;     //nao deu certo, vou testar a proxima pilha
		cont++;  //contador de pilha cheia soma 1
	}
	
}


int main(){
	
	string input;
	getline(cin, input);
	
	Armazenar_Fichas(input);
	Distribuir_Fichas();
	
	//START
	i=0;
	while(!ok){
		Verificar_Jogada();
	}
}
