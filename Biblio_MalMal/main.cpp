#include <bits/stdc++.h>
		
using namespace std;
		
void distribuirCartas(string s, string *card){
	
	//guardando todas as cartas em um vetor
	getline(cin, s);
	stringstream ss(s);
	string token;
	int i=0;
	while(ss >> token){
		card[i]=token;
		i++;
	}
}	
	
int main(){
	
	/*
	naipe ou numero
	posso jogar a carta;

	+lista de jogadores (lista)
	+cada jogador possui uma fila de 5 cartas (fila)
	+monte (fila)
 
	1 - distribuo as cartas:  
	2 -   
	*/
	
	string cartas;
	string cards[105];
	int o, jogadores;
	cin>>o;
	while(o--){
		
		cin>>jogadores;
		scanf(" ");
		distribuirCartas(cartas, cards);

	}	
}		
		
