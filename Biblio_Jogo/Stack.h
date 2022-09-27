#include "MontaNode.h"

class stack{

public:
	Node* Top;
	int N;
	
	stack();
	~stack();
	
	int size();
	bool push(int x);
	int pop();
	bool empty();
	int top();
	void clear();
};

stack::stack(){
	N=0;
	Top=0;
}

stack::~stack(){
	
	Node* p;
	while(Top){
		p = Top;
		Top=Top->Next;
		Node::DesmontaNode(p);
	}
}

int stack::size(){
	return N;
}

bool stack::push(int x){	
	Node* p = Node::MontaNode(x);
	if(!p)
		return false;
	p->Next = Top; //o node que eu criei agora aponta para o antigo top
	Top = p;
	N++;
	return true;
}

int stack::pop(){
	
	int x;
	if(Top){
		Node *p = Top;
		Top = Top->Next; 
		x = Node::DesmontaNode(p);
		N--;
	}
	return x;
}

bool stack::empty(){
	return (Top ? false : true);
}

int stack::top(){
	int x;
	if(Top)
		x = Top->D;
	return x;
}

void stack::clear(){
	
	Node* p;
	while(Top){
		p = Top;
		Top=Top->Next;
		Node::DesmontaNode(p);
	}
}





