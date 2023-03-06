#pragma once
#include "node.h"
#include "string"
#include <map>
#include <iostream>

class tree{
	
public:
	node *root;
	int n;
	std::string OriText;               //texto original
	std::string CodText;               //texto codificado
	std::map<char, std::string>code;   //codigo de cara caracter
	
	tree(){
		n=0;
		root=0;
		CodText="";
		OriText="";
	}
	
	void dicionario(){
		for(auto [a, b]: code)
			std::cout << a << " " << b << "\n";
		std::cout << "\n";
	}
	
	void codifica(std::string s){
		dfs(&root, "");        //desco ate o caracter
		                       //codifico e guardo a string codificada
		for(char k: s){
			CodText += code[k];
		}
	}
	void dfs(node **t, std::string path){
		if(!(*t)){
			return;
		}
		if((*t)->leaf){
			code[(*t)->carac] = path;
			return;
		}
		dfs(&((*t)->l), path+"0");
		dfs(&((*t)->r), path+"1");
	}

	bool search(int &valor, node**t){
		//nao encontrei
		if(!(*t))
			return false;
		if((*t)->freq == valor)
			return true;
		if((*t)->freq > valor){
			return search(valor, &((*t)->l));
		}
		return search(valor, &((*t)->r));
	}
};

