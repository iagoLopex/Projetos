#pragma once
#include "NodeD.h"

template <typename Trem>
class listDE{

public:
	NodeD<Trem>* Head;
	NodeD<Trem>* it;
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

template <typename Trem>	
listDE<Trem>::listDE(){
	Head=0;
	it=0;
	N=0;
}

template <typename Trem>
listDE<Trem>::~listDE(){
	
}

template <typename Trem>
void listDE<Trem>::itP(){
	it = it->Next;
}

template <typename Trem>
void listDE<Trem>::itS(){
	it = it->Prev;
}

template <typename Trem>
int listDE<Trem>::size(){
	return N;
}		

template <typename Trem>
bool listDE<Trem>::insert(Trem k){
	
	NodeD<Trem>* p = NodeD<Trem>::MontaNode(k);
	if(!p)
		return false;
	
	if(!Head){
		Head=it=p->Next=p->Prev=p;
	}
	else{
		p->Prev = Head->Prev;   //indexo o p no final da minha lista
		p->Next = Head;         //aponto para o inicio da lista
		(Head->Prev)->Next = p; //head aponta  para o novo fim 
		Head->Prev=p;             
		Head = p;               //o head sera sempre o ultimo node inserido
	}
	N++;
	return true;
}

template <typename Trem>
Trem listDE<Trem>::erase(){
	
	Trem x;
	if(!Head)
		return x;
	
	NodeD<Trem>* Aux = it;
	
	if(it->Next != it){//so tem um elemento
		(it->Next)->Prev = it->Prev;
		(it->Prev)->Next = it->Next;
	}
	else{//so tem um elemento
		Head=0;
	}
	
	if(Head == it)
		Head=it=it->Next;
	else
		it=it->Next;
	
	N--;
	x = NodeD<Trem>::DesmontaNode(Aux);
	return x;
}
