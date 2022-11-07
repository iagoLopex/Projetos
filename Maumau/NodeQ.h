
#pragma once

template<typename player>

class Node{

public:
	Node<player>* Next;
	player D;

	static Node<player>* MontaNode(player x);
	static player DesmontaNode(Node<player>* p);
};

template<typename player>
Node<player>* Node<player>::MontaNode(player x){
	
	Node<player>* p = new Node;
	if(p){
		p->D=x;
		p->Next=0;
	}
	return p;
}

template<typename player>
player Node<player>::DesmontaNode(Node<player>* p){
	player x;
	if(p){
		x = p->D;
		delete(p);
	}
	return x;
}
