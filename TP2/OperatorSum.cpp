#include <bits/stdc++.h>

using namespace std;

class Ponto{

private:
	int x, y;
public:
	Ponto operator + (Ponto);
	Ponto(int,int);
	virtual ~Ponto(){};
	int getx();
	int gety();
	void print();
	friend ostream &operator << (ostream &saida, Ponto &p);
};

Ponto::Ponto(int a, int b){ x = a; y = b; }

//                  forma de saida    o que quero dar print
ostream & operator << (ostream &saida, Ponto &p){
	saida << "Ponto: (" << p.getx() << " , " << p.gety() << ")" << endl;
	return saida;
}

void Ponto::print(){
	cout << x << " " << y << '\n';
}

int Ponto::getx(){
	return x;
}

int Ponto::gety(){
	return y;
}

Ponto Ponto::operator + (Ponto p){
	return Ponto(x + p.getx(), y + p.gety());
}

int main(){
	Ponto A(1,2), B(3,4);
	
	Ponto C(0,0);
	C = A + B;
	cout << C;
}
