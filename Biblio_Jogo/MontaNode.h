class Node{

public:
	Node* Next;
	int D;
	
	Node();
	static Node* MontaNode(int x);
	static int DesmontaNode(Node* p);
};

Node::Node(){
	Next=0;
	D=0;
}

Node* Node::MontaNode(int x){
	
	Node* p = new Node;
	if(p){
		p->D=x;
		p->Next=0;
	}
	return p;
}

int Node::DesmontaNode(Node* p){
	int x;
	if(p){
		x = p->D;
		delete(p);
	}
	return x;
}
