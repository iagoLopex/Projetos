#include <bits/stdc++.h>

using namespace std;

void Armazenar_Fichas(){
	
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



int main(){
	
	string input;
	getline(cin, input);
	
	map<char,int>mapa;
	vector<string>vec;
	vector<queue<string>>Jogador(4);
	vector<stack<string>>Mesa(6);
	
	

	
	Armazenar_Fichas();
	
	//armazenando as fichas, para serem destinadas a cada jogador
	while(ss>>ficha){
		vec.push_back(ficha);
		
		//guardo a ordem de prioridade dos jogadores em um mapa;
		if(ficha[1]!='P' && mapa.find(ficha[1]) == mapa.end()){
			mapa[ficha[1]]=ficha[0]-48;
		}
	}
	
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
	
	
	for(int i=0; i<4; i++){
		while(!Jogador[i].empty()){
			Mesa[i].push(Jogador[i].front()); Jogador[i].pop();
		}	
	}
	
	//se eu saio de uma pilha cheia e chego na mesma cheia finalizo
	
	//START 
	int next;
	string alf = "AVRB";
	string NextFicha;   //guardo a ficha da rodada
	int i=0;          //orienta a prioridade da jogada ( azul -> vermelho -> roxo -> branco )
	int cont=0;       //contador de pilhas cheias
	int k;            //ando pilha por pilha, a partir da pilha do indice da ficha
	bool Deu;         //verifico a jogada de cada rodada
 	bool ok  = false; //indica se todas as pilhas estao cheias, ou nao
	while(!ok){
		
		next = mapa[ alf[ (i%4) ] ]; //nessa posicao eu tenho o proximo jogador
		
		//meu vetor de jogador na fila do next, fara a proxima jogada
		//jogador[next]
		
		//eh possivel? a posicao jogador[next][1] esta cheia?
		
		cont=0;                    //contagem de pilhas cheias(reinicia a cada jogada)
		Deu=false;                 //verificar se a jogada deu certo
		NextFicha = Jogador[next].front(); //guardo a ficha a ser jogada
		k = (((Jogador[next].front())[1])-48); //inicializo k com a posicao que a ficha deve ir
		
		while(cont<=6 && !Deu){
			
			//primeiramente, se a ficha for preta ja efetuo a jogada;
			if(NextFicha[0] == 'P'){
				
				if(Mesa[ (k%6) ].size() <= 6){//se tiver elemento
					
					Mesa[ (k%6) ].pop(); //retiro o topo da pilha
					Jogador[next].pop(); //retiro a ficha do jogador
				}
				
				Deu = true;
			}
			else{//verifico se a pilha tem espaco, se nao eu tento a proxima
				
				if(Mesa[ (k%6) ].size() < 6){//tem espaco
					
					Mesa[ (k%6) ].push(NextFicha); //insiro a ficha
					Jogador[next].pop();           //retiro a ficha do jogador
					Deu = true;
				}
			}
			
			k++;     //nao deu certo, vou testar a proxima pilha
			cont++;  //contador de pilha cheia soma 1
		}
		
		if(cont == 6){//as pilhas estao todas cheias
			ok=true;
		}
		
		i++;  //vou para a proxima prioridade de cor
	}
	
	
	//---------------------------------------------------------------
	//~ imprimir a pilha
	//~ for(int i=0; i<6; i++){
		//~ cout << "pilha " << i+1 << ": \n";
		//~ while(!Mesa[i].empty()){
			//~ cout << Mesa[i].top() << " "; Mesa[i].pop();
		//~ }
		//~ cout << endl;
	//~ }
	//---------------------------------------------------------------
	//~ imprimir os jogadores
	//~ for(int i=0; i<4; i++){
		
		//~ cout << i+1 << ":  ";
		//~ while(!Jogador[i].empty()){
			//~ cout << Jogador[i].front() << " "; Jogador[i].pop();
		//~ }
		//~ cout << endl;
	//~ }
	-----------------------------------------------------------------
		
	//~teste das rodadas funcionando(o problema era o next, devia ter subtraido por 1)
	//~ for(int i=0; i<5; i++){
		
		//~ int next;
		//~ next = mapa[ alf[ (i%3) ] ];           //nessa posicao eu tenho o proximo jogador
		//~ next--;
		
		//~ cont=0;                                //contagem de pilhas cheias(reinicia a cada jogada)
		//~ Deu=false;                             //verificar se a jogada deu certo
		//~ NextFicha = Jogador[next].front();     //guardo a ficha a ser jogada
		//~ k = (((Jogador[next].front())[1])-48); //inicializo k com a posicao que a ficha deve ir
		//~ Jogador[next].pop();
		
		//~ cout << "cor " << alf[(i%3)] << "     jogador " << next << endl;
		//~ cout << NextFicha << endl;
		//~ cout << k << endl;
	//~ }
	
	
}
