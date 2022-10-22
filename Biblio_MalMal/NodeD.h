#pragma once

template<typename Trem>

class NodeD{
public:
	NodeD<Trem>* Prev;
	NodeD<Trem>* Next;
	Trem x;
	
	static NodeD<Trem>* MontaNode(Trem k);
	static Trem DesmontaNode(NodeD<Trem>* p);
};	

template<typename Trem>
NodeD<Trem>* NodeD<Trem>::MontaNode(Trem k){
	NodeD<Trem>* px = new NodeD;
	
	if(px){
		px->Next=0;
		px->Prev=0;
		px->x=k;
	}
	
	return px;
}	

template<typename Trem>
Trem NodeD<Trem>::DesmontaNode(NodeD<Trem>* p){
	
	Trem aux;
	if(p){
		aux = p->x;
		delete(p);
	}
	return aux;
}	
