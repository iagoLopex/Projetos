
#pragma once

#include "NodeQ().h"

template <typename player>
class queue{

public:
	Node<player>* head;
	Node<player>* tail;
	int N;
	
	queue();
	~queue();
	int size();
	player front();
	bool push(player x);
	player pop();
	bool empty();
};

template <typename player>
queue<player>::queue(){
	head=tail=0;
	N=0;
}

template <typename player>
queue<player>::~queue(){
	Node<player>* p;
	while(head){
		p=head;
		head=head->Next;
		Node<player>::DesmontaNode(p);
	}
}

template <typename player>
int queue<player>::size(){
	return N;
}

template <typename player>
player queue<player>::front(){
	player x;
	if(head)
		x = head->D;
	return x;
}

template <typename player>
bool queue<player>::push(player x){
	Node<player>* p = Node<player>::MontaNode(x);
	if(!p)
		return false;
	if(head)
		tail->Next=p;
	else
		head=p;
	
	tail=p;
	return true;
}

template <typename player>
player queue<player>::pop(){
	player x;
	if(head){
		Node<player>* p = head;
		head=head->Next;
		x = Node<player>::DesmontaNode(p);
		
		if(!head){
			tail=0;
		}
		
		N--;
	}
	return x;
}

template <typename player>
bool queue<player>::empty(){
	return (head ? false : true);
}
