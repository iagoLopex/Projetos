#pragma once

#include <iostream>

class nodeO{
public:
	
	nodeO*next;
	std::string d;
	
	static nodeO* montaNodeord(std::string x);
	static std::string desmontaNodeord(nodeO * x);
};

nodeO * nodeO::montaNodeord(std::string x){
	
	nodeO * a = new nodeO;
	if(a)
	{
		a->d=x;
		a->next=0;
	}
	return a;
}

std::string nodeO::desmontaNodeord(nodeO * x){
	std::string a;
	if(x)
	{
		a=x->d;
		delete x;
	}
	return a;
}

