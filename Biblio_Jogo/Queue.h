#pragma once

#include "MontaNode.h"

template <typename Trem>
class queue{

public:
	Node<Trem>* head;
	Node<Trem>* tail;
	int N;
	
	queue();
	~queue();
	int size();
	Trem front();
	bool push(Trem x);
	Trem pop();
	bool empty();
};

template <typename Trem>
queue<Trem>::queue(){
	head=tail=0;
	N=0;
}

template <typename Trem>
queue<Trem>::~queue(){
	Node<Trem>* p;
	while(head){
		p=head;
		head=head->Next;
		Node<Trem>::DesmontaNode(p);
	}
}

template <typename Trem>
int queue<Trem>::size(){
	return N;
}

template <typename Trem>
Trem queue<Trem>::front(){
	Trem x;
	if(head)
		x = head->D;
	return x;
}

template <typename Trem>
bool queue<Trem>::push(Trem x){
	Node<Trem>* p = Node<Trem>::MontaNode(x);
	if(!p)
		return false;
	if(head)
		tail->Next=p;
	else
		head=p;
	
	tail=p;
	return true;
}

template <typename Trem>
Trem queue<Trem>::pop(){
	Trem x;
	if(head){
		Node<Trem>* p = head;
		head=head->Next;
		x = Node<Trem>::DesmontaNode(p);
		
		if(!head){
			tail=0;
		}
		
		N--;
	}
	return x;
}

template <typename Trem>
bool queue<Trem>::empty(){
	return (head ? false : true);
}






