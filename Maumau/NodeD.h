
#pragma once

template <typename player>
class nodeD{
public:	
	nodeD<player>* next;
	nodeD<player>* prev;
	int d;
	
	static nodeD<player>* montaNoded(player k);
	static player desmontaNoded(nodeD<player>* x);
};

template <typename player>
nodeD<player>* nodeD<player>::montaNoded(player k){
	
	nodeD<player>* ax = new nodeD<player>;
	if(ax)
	{
		(ax)->next=0;
		(ax)->prev=0;
		((ax)->d)=k;
	}
	return ax;
}

template <typename player>
player nodeD<player>::desmontaNoded(nodeD<player>* x){
	
	player l;
	if(x)
	{
		l=(x)->d;
		delete x;
	}
	return l; 
}
