#include <bits/stdc++.h>

using namespace std;

using ld = long double;
double Toler = 0;
int iter = 0, cont = 0;
int n;
vector<ld>ant(50);
vector<ld>vec(50);
vector<ld>sol(50);
ld mat[50][50];

void printAnt();
void printMat();
void printSol();
void printVec();
void troca(int);
ld norma();
ld erro();

/*  
        Testa a convergencia de um sistema de Equacao Linear(utilizando o metodo de Sassenfeld),
    caso a convergencia seja <1, entao é possivel resolver pelo metodo de GaussSeidel, senao
    resolve pelo metodo de substituicao retroativa, pelo Metodo Direto de Gauss.
*/


//segundo
void GaussSeidel(){
	
	for(int i=0; i<n; i++)
		ant[i] = vec[i];
		
	for(int i=0; i<n; i++){
		
		ld sum=sol[i];
		for(int j=0; j<n; j++){
			
			if(i == j && mat[i][j]==0)
				troca(i);
			
			if(i != j){
				sum += ((-1) * (mat[i][j]) * ant[j]); 
			}
		}
		
		//~ cout << "linha " << i << "   sum " << sum << "  divide " << mat[i][i] << " = " << (sum)/mat[i][i] << endl;
		vec[i] = (sum)/mat[i][i];
	}
	
	cout << fixed << setprecision(4);
	//~ printAnt();
	printVec();
}

//primeiro
bool Sassenfeld(){
	
	ld sum;
	vector<ld>beta(n, 1);
	
	for(int i=0; i<n; i++){
		
		sum=0;
		for(int j=0; j<n; j++){
			
			if(i == j && mat[i][j]==0)
				troca(i);
			
			if(i!=j){
				sum += (fabs(mat[i][j] * beta[j]));
			}
		}
		beta[i] = fabs(sum/mat[i][i]);
	}
	//~ cout << "\nVetor Beta:\n";
	//~ for(int i=0; i<n; i++){
		//~ cout << "B" << i+1 << " = " << beta[i] << " \n"[i==n-1];
	//~ }
	ld conv=-1;
	for(int i=0; i<n; i++){
		conv = max(conv, beta[i]);
	}
	cout << "Convergencia: " << conv << endl;
	return (conv < 1 ? true : false);
}

//Metodo direto de Gauss
void SEL(){
	ld prev[n];
	prev[n-1] = sol[n-1] / mat[n-1][n-1];
	
	for(int i = n-2; i >= 0; i--) {
		ld sum = 0;
		for(int j = n-1; j > i; j--) {
			sum += (prev[j] * mat[i][j]);
		}
		prev[i] = (sol[i] - sum) / mat[i][i]; 
	}
	cout << fixed << setprecision(10);
	cout << "Solucao do sistema de equacao linear" << endl;
	for(int i = 0; i < n; i++) {
		cout << "Variavel X" << i + 1 << " = " << prev[i] << " " << endl;
	}
	cout << endl;
}

//Escalonar
void escalonar(){
	ld save;
	ld AB[n][n+1];
	
	//escalona com a matriz aumentada [A | B]
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			AB[i][j] = mat[i][j];
		}
	}
	for(int i=0; i<n; i++){
		AB[i][n] = sol[i];
	}
	
    for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i>j){
				save = (AB[i][j]/AB[j][j]);
				for(int k=j; k<=n; k++){
					AB[i][k]=AB[i][k]-AB[j][k]*save;
				}
			}
		}
	}
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			mat[i][j] = AB[i][j];
		}
	}
	for(int i=0; i<n; i++){
		sol[i] = AB[i][n];
	}
}

//Solucao
void solve(){
	
	if(Sassenfeld()){//se converge eu utilizo o metodo de Gauss-Seidel
		
		cout << "Converge para o Metodo de Gauss Seidel.\n\n";
		cout << setw(5) << setfill(' ') << "iter";
		cout << setw(6) << setfill(' ') << "x1";
		for(int i = 1; i < n; i++) {
			cout << setw(9) << setfill(' ') << "x" << i + 1;
		}
		cout << setw(16) << setfill(' ') << "NormaRelativa" << '\n';
		GaussSeidel();
		int c=0;
		while(norma() > Toler){
			if(c==cont) break;
			c++;
			
			GaussSeidel();
		}
	}
	else{//utilizo o metodo direto de Gauss
		
		cout << "O modelo nao converge, entao utilizo o Metodo direto de Gauss.\n\n";
		escalonar();
		printMat();
		printSol();
		SEL();
	}
}
			
int main(){ 
	
	cout << "Insira a ordem da matriz:\n";
	cin>>n;
	
	cout << "Insira a matriz:\n";
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << "digite o numero na posicao matriz["<<i+1<<"]"<<"["<<j+1<<"]: ";
			cin>>mat[i][j];
			cout << endl;
		}
	}
	cout << "Insira o vetor solucao:\n";
	for(int i=0; i<n; i++){
		cout << "digite o numero na posicao b["<<i+1<<"]: ";
		cin >> sol[i];
		cout << endl;
	}
	cout << "Insira a solucao incial aproximada x(0): \n";
	//~ vec[0] = 1.2;
	//~ vec[1] = 1.25;
	//~ vec[2] = -0.83333;
	//~ vec[3] = 0;
	for(int i=0; i<n; i++) {
		cout << "digite o numero na posicao ["<<i+1<<"]: ";
		cin >> vec[i];
		cout << "\n";
	}	
	cout << "Insira o erro: ";
	cin >> Toler;
	cout << "Insira o numero maximo de iteracoes: ";
	cin >> cont;
	cout << "\n";
	solve();
}

ld norma(){
	ld num=-1, den=-1;
	for(int i=0; i<n; i++){
		num = max(num, fabs(vec[i] - ant[i]));
		den = max(den, fabs(vec[i]));
	}
	return (num/den);
}

//Erro
ld erro(){
	
	GaussSeidel();
	ld er = -1.0;
	for(int i=0; i<n; i++)
		er = max(er, abs(vec[i] - ant[i]));
	return er;
}

//      PRINT 
void printMat(){
	cout << "Mat\n";
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printAnt(){
	cout << "Anterior\n";
	for(int i=0; i<n; i++){
		cout << "ind " << i << "  valor: " << ant[i] << " " << endl;
	}
	cout << endl;
}

void printSol(){
	cout << "Vetor Solucao\n";
	for(int i=0; i<n; i++){
		cout << sol[i] << " ";
	}
	cout << endl;
}

void printVec() {
	printf("%3d", iter++);
	for(int i = 0; i < n; i++) {
		printf("%10.5Lf", vec[i]);
	}
	printf("%10.5Lf\n", norma());
}

void troca(int i){
	int k=i;
	while(k<n && !mat[k][i]){
		k++;
	}
	if(k == n){ 
		cout << "Sem solucao\n"; 
	}
	else{//achei e troco
		
		//trocar linha de A
		int vet[n];
		for(int h=0; h<n; h++){
			vet[h] = mat[i][h];
		}
		for(int h=0; h<n; h++){
			mat[i][h] = mat[k][h];
			mat[k][h] = vet[h];
		}
		
		//trocar linha de B
		swap(sol[i], sol[k]);
	}
}

/*
 * Caso de teste
 
4
5 2 0 -1
1 8 -3 2
0 1 6 1
1 -1 2 9

6
10 
-5
0

1.2
1.25
-0.83333
0

0.001
50

---------------------

algoritmos numericos frederico pdf

*/
