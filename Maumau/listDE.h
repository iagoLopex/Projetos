
#pragma once

#include "NodeD().h"

template <typename t>

class listDE{
public:
	nodeD<t> * h;
	nodeD<t> * it;
	int n;
	
	listDE();
	~listDE();
	bool insert(t x);
	t erase();
	void clear();
	void itpf();
	void itpt();
	void itbegin();
	t returnit();
	bool empty();
	int size();
	bool search(int x);
};

template <typename t>
listDE<t>::listDE () {
	h=0,it=0;
	n=0;
}

template <typename t>
listDE<t>::~listDE () {
	
	if(h)
	{
		nodeD<t> * a = h->next;
		while(a!=h)
		{
			nodeD<t> * ax=a->next;
			nodeD<t>::desmontaNoded(a);
			a=ax;
		}
		nodeD<t>::desmontaNoded(h);
	}
}

template <typename t>
bool listDE<t>::insert (t x) {
	
	nodeD<t> * p = nodeD<t>::montaNoded(x);
	if(!p)
		return false;
	
	if(!h)
	{
		it=p,h=p,p->prev=p,p->next=p;
	}
	else
	{
		p->prev=h->prev;
		p->next=h;
		(h->prev)->next=p;
		h->prev=p;
		h=p;
	}
	n++;
	return true;
}

template <typename t>
t listDE<t>::erase () {
	
	t x=0;
	nodeD<t> * a = it;
	if(!h)
		return x;
	
	if(h==it)
		h=h->next;
		
	if(h==h->next)
	{
		it=h=0;
	}
	else
	{
		it->next->prev=it->prev;
		it->prev->next=it->next;
		it=h;
	}
	x = nodeD<t>::desmontaNoded(a);
	n--;
	return x;	
}

template <typename t>
void listDE<t>::clear () {
	
	if(h)
	{
		nodeD<t> * a = h->next;
		while(a!=h)
		{
			nodeD<t> * ax=a->next;
			nodeD<t>::desmontaNoded(a);
			a=ax;
		}
		nodeD<t>::desmontaNoded(h);
	}
	it=0,h=0;
	n=0;
}

template <typename t>
void listDE<t>::itpf () {
	
	if(it)
		it=it->next;
}

template <typename t>
void listDE<t>::itpt () {
	
	if(it)
		it=it->prev;
}

template <typename t>
void listDE<t>::itbegin () {
	it=h;
}

template <typename t>
t listDE<t>::returnit () {
	
	t a;
	if(it)
		a=it->d;
		
	return a;
}

template <typename t>
bool listDE<t>::empty () {
	
	return !h;
}

template <typename t>
bool listDE<t>::search (int x) {
		
	if(h)
	{
		nodeD<t> * a = it;
		it=it->next;
		while(it!=a && (it->d)!=x)
		{
			it=it->next;
		}
		if((it->d)==x)
		{
			return true;
		}
	}
	return false;
}

template <typename t>
int listDE<t>::size () {
	
	return n;
}

