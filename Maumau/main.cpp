
#include <iostream>
#include "game().h"

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

int main(){
	
	string cartas;
	int o;          //numero de partidas
	int jogadores;  //numero de jogadores
	cin>>o;
	while(o--){
		
		cin>>jogadores;
		scanf(" ");
		getline(cin, cartas);
		
		game maumau(cartas, jogadores);
	}	
}

