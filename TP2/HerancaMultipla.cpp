#include <bits/stdc++.h>

using namespace std;

class A{
public:
	A(int x){cout << "construtor A" << endl;}
};

class B{
public:
	B(int x){cout << "construtor B" << endl;}
};

class C{
public:
	C(int x){cout << "construtor C" << endl;}
};

class D: public A, public B, public C{//se inverter a ordem de chamada dos construtores sera alterada
protected:
	int d;
public:
	D(int x, int y, int z, int w) : A(x), B(y), C(z){
		d=w;
	}
};

int main(){
	//~ A o1;
	//~ B o2;
	//~ C o3;
}
