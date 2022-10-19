#pragma once
#include "Trem.h"

class NodeD{
public:
	NodeD* Prev;
	NodeD* Next;
	Trem x;
	
	NodeD();
	~NodeD();
	
	static NodeD* MontaNode(Trem k);
	static Trem DesmontaNode(NodeD *p);
};	
	
NodeD* NodeD::MontaNode(Trem k){
	NodeD* px = new NodeD;
	
	if(px){
		px->Next=0;
		px->Prev=0;
		px->x=k;
	}
	
	return px;
}	
	
Trem NodeD::DesmontaNode(NodeD *p){
	
	Trem aux;
	if(p){
		aux = p->x;
		delete(p);
	}
	return aux;
}	
