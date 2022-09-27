#include "MontaNode.h"

class queue{

public:
	Node* head;
	Node* tail;
	int N;
	
	queue();
	~queue();
	int size();
	int front();
	bool push(int x);
	int pop();
	bool empty();
};

queue::queue(){
	head=tail=0;
	N=0;
}

queue::~queue(){
	Node* p;
	while(head){
		p=head;
		head=head->Next;
		Node::DesmontaNode(p);
	}
}

int queue::size(){
	return N;
}

int queue::front(){
	int x;
	if(head)
		x = head->D;
	return x;
}

bool queue::push(int x){
	Node* p = Node::MontaNode(x);
	if(!p)
		return false;	
	p->Next = head;
	head=p;
	return true;
}

int queue::pop(){
	int x;
	if(head){
		Node* p = head;
		head=head->Next;
		x = Node::DesmontaNode(p);
		
		if(!head){
			tail=0;
		}
		
		N--;
	}
	return x;
}

bool queue::empty(){
	return (head ? false : true);
}






