
#pragma once

#include "NodeLSO().h"

class ListaS{

public:
	nodeO* h;
	int n;
	ListaS();
	~ListaS();
	void insert(std::string c);
	bool pop(std::string & c);
	int size();
	bool vazio();
	void clear();
};

ListaS::ListaS(){
	h=0;
	n=0;
}

ListaS::~ListaS(){
	
	if(h)
	{
		nodeO * aux=h;
		h=h->next;
		while(h)
		{
			nodeO::desmontaNodeord(aux);
			aux=h;
			h=h->next;
		}
	}
}

void ListaS::insert(std::string c) {

	nodeO * a = nodeO::montaNodeord(c);
	if(!h)
	{
		h=a;
	}
	else
	{
		nodeO**it=&h;
		while((*it)->next && ((*it)->d[0]>c[0] || ((*it)->d[0]==c[0] && (*it)->d[1]<=c[1])))
		{
			it=&((*it)->next);
		}
		if((*it)->d[0]>c[0] || ((*it)->d[0]==c[0] && (*it)->d[1]<c[1]))
		{	
			(*it)->next=a;
		}
		else
		{
			a->next=(*it);
			(*it)=a;	
		}
	}
	n++;
}

bool ListaS::pop(std::string & c){
	
	if(!h)
	{
		return false;
	}
	nodeO** it=&h;
	while((*it)->next && ((*it)->d[0]!=c[0] && (*it)->d[1]!=c[1]))
	{
		it=&((*it)->next);
	}
	if((*it)->d[0]==c[0]||(*it)->d[1]==c[1])
	{
		nodeO*aux=*it;
		(*it)=(*it)->next;
		c=nodeO::desmontaNodeord(aux);
		n--;
		return true;
	}
	return false;
}

int ListaS::size(){
	
	return n;
}

bool ListaS::vazio(){
	
	return !n;
}

void ListaS::clear(){
	
	if(h)
	{
		nodeO * aux=h;
		h=h->next;
		while(h)
		{
			nodeO::desmontaNodeord(aux);
			aux=h;
			h=h->next;
		}
	}
	n=0;
}

