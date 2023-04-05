#pragma once

class node{

public:
	int freq;
	bool leaf;
	char carac;
	node *r;
	node *l;
	
	node(){
		r=l=0;
		freq=0;
		leaf=false;
	}
};
