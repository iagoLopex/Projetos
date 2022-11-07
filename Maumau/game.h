#pragma once

using namespace std;

#include <sstream>
#include "listDE().h"
#include "player().h"
#include "Queue().h"
#include "ListaSO().h"

class game{
public:
	
	nodeD<int>* u;              //variavel para decidir o proximo jogador (comeco do proximo, o primeiro ja jogou)
	bool orientacao;            //determina a orientacao do jogador (1 horario, 0 anti-h)
	string lixo;                //determina o tipo e naipe da proxima carta a ser jogada
	ListaS* Deck;               //ponteiro para o Deck de cada jogador
	listDE<int> ind_Jogadores;  //o index dos jogadores presentes na partida
	queue<string>monte;         //monte de cartas
	int nj;                     //numero de jogadores atuais
	
	game(string s, int jog);
	void Distribuir();
	void start();
	void Retirar_Perdedor();
	void Verificar_tipo();
	void Reset();
};

game::game(string s, int jog){
	
	//orientacao inicial é horaria
	orientacao=1;
	
	//guardo o numero de jogadores
	nj=jog;
	
	//insiro as cartas no monte
	stringstream ss(s);
	string token;
	while(ss >> token){
		monte.push(token);
	}
	
	//crio um vetor de lista ordenada, mao dos players
	Deck = new ListaS[nj];
	
	//coloco os jogadores na partida
	for(int i=0; i<nj; i++)
		ind_Jogadores.insert(i);
	
	//distribuo as cartas para os jogadores
	Distribuir();
	
	//inicio o jogo
	start();
}

void game::Distribuir(){
	
	//insiro a primeira carta no lixo
	lixo = monte.pop();
	
	//distribuo 4 cartas para o 1 jogador inicialmente
	for(int j=0; j<4; j++){
		Deck[0].insert(monte.pop());
	}
	
	//distribuo 5 para cada um dos restantes
	for(int i=1; i<nj; i++){
		for(int j=0; j<5; j++){
			Deck[i].insert(monte.pop());
		}
	}
}

void game::start(){
	
	//variavel pra insetrir a carta anterior do lixo no monte
	string ant;
	
	//boleana que indica o fim de uma rodada
	bool finish;
	
	//variavel para decidir o proximo jogador (comeco do proximo, o primeiro ja jogou)
	u = ind_Jogadores.it->next;  
	
	//variavel para verificar quantas cartas o jogador atual possui
	nodeD<int>* guard = u;
	
	//enquanto tiver mais de um jogador o jogo continua
	while(nj>1){
		
		finish=false;

		//cada rodada so termina quando um jogador terminar suas cartas
		while(!finish){
			
			ant = lixo;
			
			//guardo o jogador atual
			guard = u;
			
			//verifico se o jogador atual possui a carta
			if(Deck[ u->d ].pop(lixo)){           //retiro a carta da mao do jogador, se for true, ja coloco no lixo
				
				//cout << u->d << endl;
				Verificar_tipo();                 //verifico a carta que foi jogada no lixo e realizo as penalidades
				monte.push(ant);                  //se ele tem a carta eu tirei da mao e a carta anterior do lixo vai pro monte
			}
			else{                                 //o jogador dev comprar uma carta do monte        
				//cout<<"asdoinasd"<<endl;
				Deck[ u->d ].insert(monte.pop()); //o mesmo jogador tenta novamente
				
				if(Deck[ u->d ].pop(lixo)){       //verifico novamente se ele pode jogar
					
					Verificar_tipo();             //verifico a carta que foi jogada no lixo e realizo as penalidades
					monte.push(ant);              //coloco a carta que estava no lixo no monte 
				}
				else{                             //o jogador nao conseguiu jogar, passo a vez
					if(orientacao){              
						u = u->prev;
					}
					else{
						u = u->next;
					}
				}
			}
			
			//apos a jogada verifico se o jogador terminou suas cartas
			if(!Deck[ guard->d ].size()){
				//cout<<"acucucucucucucucuj"<<endl;
				nj--;                            //retiro o jogador 
				finish = true;                   //finalizo a rodada
				Retirar_Perdedor();              //retiro o perdedor da rodada
			}
		}
		
		//reseto as cartas dos jogadores
		Reset();
		
		//redistribuo as cartas para uma nova rodada
		Distribuir();
	}
	
	//so restou um jogador
	cout << "Vencedor " << endl;
	cout << ind_Jogadores.h->d << endl;
}

void game::Verificar_tipo(){
	
	if(lixo[0] == 'L')//mudo a orientacao
	{
		orientacao = !orientacao;
		if(orientacao){
			u = u->prev;
		}
		else{
			u = u->next;
		}
	}
	else{
		if(lixo[0] == 'G')//dou 2 cartas ao proximo jogador
		{
			if(orientacao)//se for horario
			{
				for(int i=0; i<2; i++)
					Deck[ (u->prev)->d ].insert(monte.pop());
				
				u = u->prev;
			}
			else
			{
				for(int i=0; i<2; i++)
					Deck[ (u->next)->d ].insert(monte.pop());
				
				u = u->next;
			}
		}
		else{
			if(lixo[0] == 'I')//dou 3 cartas ao anterior
			{
				if(orientacao)//se for horario
				{
					for(int i=0; i<3; i++)
						Deck[ (u->next)->d ].insert(monte.pop());
					
					u = u->prev;
				}
				else{
					for(int i=0; i<3; i++)
						Deck[ (u->prev)->d ].insert(monte.pop());
					
					u = u->next;
				}
			}
			else{
				if(lixo[0] == 'A')//impedir o proximo de jogar
				{
					if(orientacao){
						u = (u->prev)->prev;
					}
					else{
						u = (u->next)->next;
					}
				}
				else//carta normal
				{
					if(orientacao){
						u = u->prev;
					}
					else{
						u = u->next;
					}
				}
			}
		}
	}
}

void game::Reset(){
	
	nodeD<int>* go = ind_Jogadores.h;
	int k = ind_Jogadores.n;
	
	while(k--){                         //vou pra cada jogador 
		
		nodeO* a = Deck[ go->d ].h; 
		while(a){                       //pego todas as cartas desse jogador e re-insiro no monte 
			monte.push( a->d );         //insiro no monte
			a = a->next;
		}
		Deck[ go->d ].clear();          //retiro todas as cartas da mao de cada jogador
		
		go = go->next;
	}
}

void game::Retirar_Perdedor(){
	
	nodeD<int>* go = ind_Jogadores.h;   //varrer todos os index dos jogadores
	
	int maior=-1;
	int k = ind_Jogadores.size();
	while(k--){                         //enquanto eu ainda nao foi
		
		if(Deck[ go->d ].n > maior)     //guardo o jogador com mais cartas
			maior = Deck[ go->d ].n;
			
		go = go->next;
	}
	if(ind_Jogadores.search(maior))     //retiro o jogador da partida
		ind_Jogadores.erase();
}
