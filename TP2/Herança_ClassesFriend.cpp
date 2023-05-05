#include <bits/stdc++.h>

using namespace std;

class colchao{
private:
	string densidade;
	double preco;
	
public:
	
	colchao(string dens, double valor){
		densidade=dens;
		preco=valor;
	}
	
	double getPreco(){
		return preco;
	}
	
	string getDensidade(){
		return densidade;
	}
	
	friend void dados();
};

class molas : public colchao{
private:
	string tamanho;

public:
	molas(string tam, string den, double valor) : colchao(den, valor) {
		tamanho=tam;
	}
	void dados(){
		cout << "densidade " << getDensidade() << endl;
		cout << "preco " << getPreco() << endl;
		cout << "tamanho " << tamanho << endl << endl;
	}
};

class espuma : public colchao{
private:
	string tamanho;
public:
	espuma(string tam, string den, double valor) : colchao(den, valor) {
		tamanho=tam;
	}
	void dados(){
		cout << "densidade " << getDensidade() << endl;
		cout << "preco " << getPreco() << endl;
		cout << "tamanho " << tamanho << endl << endl;
	}
};

int main(){
	espuma a("solteiro", "alta", 3000.0);
	molas b("king size", "baixa", 9000.0);
	
	a.dados();
	b.dados();
}


/*-----------------------------com sobrecarga de metodo------------------------------------------*/

#include <bits/stdc++.h>

using namespace std;

class colchao{
private:
	string densidade;
	double preco;
	
public:
	
	colchao(string dens, double valor){
		densidade=dens;
		preco=valor;
	}
	
	double getPreco(){
		return preco;
	}
	
	string getDensidade(){
		return densidade;
	}
	
	friend void dados();
};

class molas : public colchao{
public:
	string tamanho;

public:
	molas(string tam, string den, double valor) : colchao(den, valor) {
		tamanho=tam;
	}
};

class espuma : public colchao{
public:
	string tamanho;
public:
	espuma(string tam, string den, double valor) : colchao(den, valor) {
		tamanho=tam;
	}
};

void dados(molas &a){
	cout << "densidade " << a.getDensidade() << endl;
	cout << "preco " << a.getPreco() << endl;
	cout << "tamanho " << a.tamanho << endl << endl;
}

void dados(espuma &a){
	cout << "densidade " << a.getDensidade() << endl;
	cout << "preco " << a.getPreco() << endl;
	cout << "tamanho " << a.tamanho << endl << endl;
}

int main(){
	espuma a("solteiro", "alta", 3000.0);
	molas b("king size", "baixa", 9000.0);
	
	dados(a);
	dados(b);
}
