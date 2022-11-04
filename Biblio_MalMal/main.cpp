#include <iostream>
#include <sstream>
#include "listDE.h"
#include "Trem.h"
#include "Queue.h"

using namespace std;

//  0    1      2      3 
// paus copas espada  ouro 

/*
Pontuação:
	A (ás) = 1 ponto
	B (dois) = 2 pontos
	C (três) = 3 pontos
	D (quatro) = 4 pontos
	E (cinco) = 5 pontos
	F (seis) = 6 pontos
	G (sete) = 7 pontos
	H (oito) = 8 pontos
	I (nove) = 9 pontos
	J (dez) = 10 pontos
	K (valete) = 11 pontos
	L (dama) = 12 pontos
	M (rei) = 13 pontos 
*/

void start(){
	
}

void distribuirCartas(string s, int n, listDE<Trem>&partida, queue<string>&monte){
	
	//guardando todas as cartas
	getline(cin, s);
	stringstream ss(s);
	string token;
	string y[105];
	int i=0;
	while(ss >> token){
		y[i]=token; i++;
	}
	
	Trem aux;
	string cart[5];
	int k=0; //index do jogador
	
	//distribuindo conjuntos de 5 cartas
	for(i=1; i<=5*n; i++){              //numero de cartas a serem distribuidas
		
		if(!(i%5)){                     //ultima carta a ser dada para aquele jogador
			aux.cards[ 4 ] = y[ i-1 ];
			aux.index = k;
			k++;                        //vou pro proximo jogador
			partida.insert(aux);        //insiro o jogador atual
		}
		else{
			aux.cards[ (i%5)-1 ] = y[ i-1 ];
		}
	}
	
	int u=i;
	
	
	//insiro o restante no monte
	for(i=u-1; i<104; i++){
		cout << i << " " << y[i] << endl;
	}
	
	while(monte.size()){
		cout << monte.pop() << " ";
	}

	
	/*
	//jogadores
	for(i=0; i<n; i++){
		cout << endl;
		for(int j=0;j<5; j++)
			cout << partida.it->x.cards[j] << " ";
		partida.itS();
	}
	*/
}

int main(){

	string cartas;
	int o;  //numero de partidas
	int n;  //numero de jogadores
	cin>>o;
	while(o--){
		cin>>n;
		listDE<Trem>partida;  //circulo de jogadores
		queue<string>monte;     //monte de cartas
		
		scanf(" ");
		
		distribuirCartas(cartas, n, partida, monte);
		start();
	}	
}		
