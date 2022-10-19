#pragma once
#include "NodeD.h"

class listDE{
	
	NodeD* Head;
	NodeD* it;
	int N;
	
	listDE();
	~listDE();
	bool insert(Trem k);
	int size();
	Trem erase();
	void itP();
	void itS();
	void itBegin();
	void itEnd();
	Trem TremIt();
	bool Empty();
	bool Search(int x);
};
		
listDE::listDE(){
	Head=0;
	it=0;
	N=0;
}
		
listDE::~listDE(){
	
}

void listDE::itP(){
	it = it->Next;
}

void listDE::itS(){
	it = it->Prev;
}

int listDE::size(){
	return N;
}		

bool listDE::insert(Trem k){
	
	NodeD* p = NodeD::MontaNode(k);
	if(!p)
		return false;
	
	if(!Head){
		Head=it=p->Next=p->Prev=p;
	}
	else{
		p->Prev = Head->Prev;   //indexo o p no final da minha lista
		p->Next = Head;         //aponto para o inicio da lista
		(Head->Prev)->Next = p; //head aponta para o novo fim 
		Head = p;               //o head sera sempre o ultimo no inserido
	}
	N++;
	return true;
}	
	
Trem listDE::erase(){
	
	Trem x;
	if(!Head)
		return x;
	
	NodeD* Aux = it;
	
	if(it->Next != it){//so tem um elemento
		(it->Next)->Prev = it->Prev;
		(it->Prev)->Next = it->Next;
	}
	else{//so tem um elemento
		Head=0;
	}
	N--;
	x = NodeD::DesmontaNode(Aux);
	return x;
}
