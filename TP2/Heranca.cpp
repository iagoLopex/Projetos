#include <bits/stdc++.h>

using namespace std;

class Professor{
private:
	long matricula;
	long rg;
	
protected:
	string nome;
	
public:
	
	Professor(){
		matricula = 1000;
		rg = 10000002;
	}

	string getNome(){
		return nome;
	}
	long getMatricula(){
		return matricula;
	}
	long getRg(){
		return rg;
	}
	
	void setMatricula(long x){
		matricula=x;
	}
	void setRg(long x){
		rg=x;
	}
};


class ProfessorPuc : public Professor {

private:
	int cargaHoraria;
	float salario;
	char turno;

public:
	int getCarga(){
		return cargaHoraria;
	}
	float getSalario(){
		return salario;
	}
	char getTurno(){
		return turno;
	}
	
	void setCarga(int x){
		cargaHoraria=x;
	}
	void setSalario(float x){
		salario=x;
	}
	void setTurno(char x){
		turno=x;
	}
	void setNome(string x){
		nome=x;
	}
};

int main(){
	
	Professor p;
	cout << "Nome: " << p.getNome() << endl;
	cout << "Matricula: " << p.getMatricula() << endl;
	cout << "Rg: " << p.getRg() << endl << endl;
	
	ProfessorPuc A;
	A.setNome("Test");
	A.setMatricula(1001);
	A.setRg(2002);
	A.setCarga(14);
	A.setTurno('N');
	
	cout << A.getNome() << endl;
	cout << A.getMatricula() << endl;
	cout << A.getRg() << endl;
	cout << A.getCarga() << endl << endl;
	
	if(A.getTurno() == 'N') cout << "noturno\n";
	if(A.getTurno() == 'M') cout << "matutino\n";
	if(A.getTurno() == 'V') cout << "vespertino\n";
}
