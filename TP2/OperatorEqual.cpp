#include <bits/stdc++.h>

using namespace std;

class aluno{

private:
	string nome;
	int mat;
public:
	aluno(string, int);
	virtual ~aluno(){};
	string getnome();
	int getmat();
	bool operator == (aluno& A);
	friend ostream &operator<<(ostream & saida, aluno & A);
};

aluno::aluno(string n, int m){
	nome=n;
	mat=m;
}

string aluno::getnome(){
	return nome;
}

int aluno::getmat(){
	return mat;
}

bool aluno::operator == (aluno & Aluno){
	if(mat==Aluno.getmat() && nome==Aluno.getnome())
		return true;
	return false;
}

ostream &operator<<(ostream & saida, aluno & A){
	saida<<"Aluno:\n";
	saida<<"nome: " << A.getnome() << '\n';
	saida<<"mat: " << A.getmat() << '\n';
	return saida;
}

int main(){
	
	aluno a("iago", 2021);
	aluno b("iago", 2021);
	
	cout << (a==b);
}
