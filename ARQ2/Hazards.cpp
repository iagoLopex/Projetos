#include <bits/stdc++.h>
#define sz(x) (int)x.size()
using namespace std;

const int MAXN = 1e6;
string mat[1000][1000];
bool stall[1000][1000];

struct Using{
	map<string, int>mp; //guardar o tempo em que cada registrador estará livre
	vector<int>Memo;    //verificar em quais ciclos de clock a memoria esta sendo usada
	Using(){
		Memo.resize(MAXN, 0);
	}
};

struct instrucao{
	string type, receive, in; //tipo da instrucao, quem recebe o valor, e a instrucao completa
	vector<string>factor;     //registradores utilizados na instrucao 
	
	instrucao(){}
	instrucao(string str){
		in = str;
		int i = 0;
		stringstream ss(str);
		string token;
		
		while(ss>>token){
			if(i == 0){
				type = token;
			}
			else{
				string aux = "";
				for(char k: token) if(k != ',') aux+=k;
				if(i == 1){
					receive = aux;
					factor.push_back(aux);
				}
				else{
					factor.push_back(aux);
				}
			}
			i++;
		}
	}
	void printIns(){
		cout << in << " | ";
	}
};

void pipe(int line, int x){
	vector<string>op = {"BI", "DI", "EX", "M ", "R "};
	for(int j=x, i=0; j<x+5; j++, i++)
		mat[line][j] = op[i];
}

void print(){
	vector<string>op = {"BI", "DI", "EX", "M ", "R "};
	for(auto k: op)
		cout << k << " ";
}

void run(){
	
	Using U;
	string str;
	int clock = 0;
	vector<instrucao>ins;
	vector<int>tipo(1000, -1);
	
	getline(cin, str);
	while(str.size()){//ler as instrucoes e colocar no vetor de instrucoes 
		instrucao a(str);
		ins.push_back(a);
		getline(cin, str);
	}
	
	for(int i=0; i<1000; i++){
		for(int j=0; j<1000; j++){
			mat[i][j]="  ";
			stall[i][j]=0;
		}
	}
	
	for(int i=0; i<sz(ins); i++, clock++){
		if(ins[i].type == "JMP" || ins[i].type == "JZ"){//se houve um jump eu so finalizo
			tipo[i] = 3;//hazard de controle
		}
		else{
			if(U.Memo[clock]){//se eu vou buscar a instrucao e a memoria ja esta sendo usada naquele clock
				while(U.Memo[clock]){
					stall[i][clock]=1;
					clock++; //enquanto a memoria estiver sendo utilizada naquele ciclo de clock eu continuo andando os clocks
				}
				tipo[i] = 2;//hazard estrutural
			}
			else{
				for(auto k: ins[i].factor){ //para cada registrador que esta sendo utilizado para fazer a operacao eu verifico se ele esta livre
					if(U.mp[k] > clock){ //se o tempo de clock do registrador for maior significa que ele so vai terminar de ser usado no tempo U.mp[k]
						while(clock<=U.mp[k]){ //enquanto o clock de agora for menor que o tempo de saida do registrador eu continuo andando os clocks
							stall[i][clock]=1;
							clock++;
						}
						tipo[i] = 1;//hazard de dados
					}
				}
			}
		}
		pipe(i, clock);
		U.Memo[clock] = U.Memo[clock+3] = 1; //identifico em quais ciclos de clock a memoria vai estar ocupada
		
		if(ins[i].type != "ST")
			U.mp[ins[i].receive] = clock+3; //o registrador que vai receber o valor so vai estar disponivel no clock+3 
	}
	
	//imprime o pipeline
	for(int i=0; i<sz(ins); i++){
			
		ins[i].printIns();
		bool flag=false;
		for(int j=0; !flag && j<clock+10; j++){
			
			int at = j;
			while(stall[i][at]) cout << "[] ", at++;
			
			flag |= (at != j);
			
			if(flag){
				print();
				if(tipo[i] == 1) cout << " -> Hazard de dados, registrador ainda nao pode ser acessado nesse clock";
				if(tipo[i] == 2) cout << " -> Hazard Estrutural, acesso a memoria na busca da instrucao";
				if(tipo[i] == 3){ cout << " -> Hazard de Controle, instrucao de salto de label\n"; return; }
			}
			else{
				cout << mat[i][j] << " ";
				if(mat[i][j] == "R "){
					if(tipo[i] == 1) cout << " -> Hazard de dados, registrador ainda nao pode ser acessado nesse clock";
					if(tipo[i] == 2) cout << " -> Hazard Estrutural, acesso a memoria na busca da instrucao";
					if(tipo[i] == 3){ cout << " -> Hazard de Controle, instrucao de salto de label\n"; return; }
				}
			}
		}
		cout << endl;
	}
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);#include <bits/stdc++.h>
#define sz(x) (int)x.size()
using namespace std;

const int MAXN = 1e6;
string mat[1000][1000];
bool stall[1000][1000];

struct Using{
	map<string, int>mp; //guardar o tempo em que cada registrador estará livre
	vector<int>Memo;    //verificar em quais ciclos de clock a memoria esta sendo usada
	Using(){
		Memo.resize(MAXN, 0);
	}
};

struct instrucao{
	string type, receive, in; //tipo da instrucao, quem recebe o valor, e a instrucao completa
	vector<string>factor;     //registradores utilizados na instrucao 
	
	instrucao(){}
	instrucao(string str){
		in = str;
		int i = 0;
		stringstream ss(str);
		string token;
		
		while(ss>>token){
			if(i == 0){
				type = token;
			}
			else{
				string aux = "";
				for(char k: token) if(k != ',') aux+=k;
				if(i == 1){
					receive = aux;

	int cases = 9;
	while(cases--) {
		run();
		cout << '\n';
	}
}

/*

ADD R1, R2, R3
ADD R4, R1, R5

ADD R1, R2, R3
ADD R2, R3, R4
ADD R3, R4, R5
ADD R4, R5, R6

ADD R1, R2, R3
ADD R2, R1, R3
ADD R3, R2, R1

ST R1, [X]
LD R2, [X]

ST R1, [X]
LD R1, [X]

LD R1, [X]
ST R1, [X]

ST R1, [X]
LD R1, [X]
ST R1, [X]

LD R1, [X]
JMP label1

LD R2, [X]
JZ R1, Lab

*/
