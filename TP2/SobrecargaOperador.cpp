#include <bits/stdc++.h>

using namespace std;

class player{

private:
	int forca, resistencia, inteligencia;
	
public:
	
	player(){
		srand(time(0));
		forca = rand() % 100;
		resistencia = rand() % 100;
		inteligencia = rand() % 100;
	};
	
	int getF(){ return forca; }
	int getR(){ return resistencia; }
	int getI(){ return inteligencia; }
	
	void setF(int x){ forca = x; }
	void setR(int x){ resistencia = x; }
	void setI(int x){ inteligencia = x; }
	
	int poder(){
		return (forca*3+inteligencia*4+resistencia*2);
	}
	
	bool operator > (player & A){
		if(poder() > A.poder())
			return true;
		return false;
	}
	
	friend ostream &operator<<(ostream & saida, player & A){
		saida<<"Player:\n";
		saida<<"forca: " << A.getF() << '\n';
		saida<<"resistencia: " << A.getR() << '\n';
		saida<<"inteligencia: " << A.getI() << '\n';
		saida<<"Poder: " << A.poder() << '\n';
		return saida;
	}
};

int main(){
	
	player p1, p2;
	cout << p1;
	cout << endl;
	cout << p2;
	cout << endl;
	
	cout << (p1>p2 ?  "p1 Wins!" : "p2 wins!") << endl; 
}
