#pragma once
#include "MontaNode.h"

template <typename Trem>
class stack{

public:
	Node<Trem>* Top;
	int N;
	
	stack();
	~stack();
	
	int size();
	bool push(Trem x);
	Trem pop();
	bool empty();
	Trem top();
	void clear();
};

template <typename Trem>
stack<Trem>::stack(){
	N=0;
	Top=0;
}

template <typename Trem>
stack<Trem>::~stack(){
	
	Node<Trem>* p;
	while(Top){
		p = Top;
		Top=Top->Next;
		Node<Trem>::DesmontaNode(p);
	}
}

template <typename Trem>
int stack<Trem>::size(){
	return N;
}

template <typename Trem>
bool stack<Trem>::push(Trem x){	
	Node<Trem>* p = Node<Trem>::MontaNode(x);
	if(!p)
		return false;
	p->Next = Top; //o node que eu criei agora aponta para o antigo top
	Top = p;
	N++;
	return true;
}

template <typename Trem>
Trem stack<Trem>::pop(){
	
	Trem x;
	if(Top){
		Node<Trem> *p = Top;
		Top = Top->Next; 
		x = Node<Trem>::DesmontaNode(p);
		N--;
	}
	return x;
}

template <typename Trem>
bool stack<Trem>::empty(){
	return (Top ? false : true);
}

template <typename Trem>
Trem stack<Trem>::top(){
	int x;
	if(Top)
		x = Top->D;
	return x;
}

template <typename Trem>
void stack<Trem>::clear(){
	
	Node<Trem>* p;
	while(Top){
		p = Top;
		Top=Top->Next;
		Node<Trem>::DesmontaNode(p);
	}
}





