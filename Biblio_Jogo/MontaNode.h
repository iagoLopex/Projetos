#pragma once

template<typename Trem>

class Node{

public:
	Node<Trem>* Next;
	Trem D;

	static Node<Trem>* MontaNode(Trem x);
	static Trem DesmontaNode(Node<Trem>* p);
};

template<typename Trem>
Node<Trem>* Node<Trem>::MontaNode(Trem x){
	
	Node<Trem>* p = new Node;
	if(p){
		p->D=x;
		p->Next=0;
	}
	return p;
}

template<typename Trem>
Trem Node<Trem>::DesmontaNode(Node<Trem>* p){
	Trem x;
	if(p){
		x = p->D;
		delete(p);
	}
	return x;
}
