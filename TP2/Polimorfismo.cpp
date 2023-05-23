#include <bits/stdc++.h>

using namespace std;


class figura{
public:
	virtual void print(){
		cout << "figura " << endl;
	}
};

class triangulo:public figura{
public:
	void print(){
		cout << "triangulo " << endl;
	}
};

class circulo:public figura{
public:
	void print(){
		cout << "circulo " << endl;
	}	
};

class quadrado:public figura{
public:
	void print(){
		cout << "quadrado " << endl;
	}
};

int main(){
	
	figura *ptr[3];
	
	quadrado fig1;
	circulo fig2;
	triangulo fig3;
	
	ptr[0] = &fig1;
	ptr[1] = &fig2;
	ptr[2] = &fig3;
	
	for(int i=0; i<3; i++){
		ptr[i]->print();
	}
}

/*
#include <bits/stdc++.h>

using namespace std;

//POLIMORFISMO DINAMICO

class componente{
public:
	virtual void exibe() const{
		cout << "Componente exibe " << endl;
	}
};

class botao: public componente{
public:
	void exibe() const{
		cout << "Botao exibe " << endl;
	}
};

class janela : public componente{
public:
	void exibe() const{
		cout << "Janela exibe " << endl;
	}
};

void manipula(const componente &c){
	c.exibe();
}

int main(){
	
	botao ok;
	janela ajuda;
	manipula(ok);
	manipula(ajuda);
	return 0;
}
*/
