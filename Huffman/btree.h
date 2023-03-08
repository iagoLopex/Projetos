#pragma once
#include "node.h"
#include "string"
#include <map>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define f first
#define s second

using namespace std;

class huffman{
	
public:
	node *root;
	int n;
	std::string OriText;               //texto original
	std::string CodText;               //texto codificado
	std::map<char, std::string>code;   //codigo de cara caracter
	std::map<char, int>mp;
	std::priority_queue<std::pair<int,node*>, std::vector<std::pair<int, node*>>, std::greater<std::pair<int,node*>> >pq;
	
	void build(){
		
		//armazeno um mapa de frequencias dos caracteres
		for(char k: OriText){
			mp[k]++;
		}
		
		//insiro os primeiros nodes na fila
		for(auto [a, b]: mp){
			node *c = new node;
			c->leaf=1;
			c->freq=b;
			c->carac=a;
			pq.push({b, c});
		}
		
		//equanto eu nao terminar de montar a arvore, eu continuo unindo os nodes
		while(pq.size()>1){
			node *a = pq.top().s; pq.pop();
			node *b = pq.top().s; pq.pop();
			node *c = new node;
			c->r = a;
			c->l = b;
			int k = a->freq + b->freq;
			c->freq = k;  
			pq.push({k, c});
		}
		
		//insiro o node que contem a arvore no root
		root = pq.top().s; pq.pop();
		
		//gera uma string codificada e um dicionario dos codigos dos caracteres
		codifica(OriText);
	}
	
	huffman(std::string str){
		n=0;
		root=0;
		CodText="";
		OriText=str;
		
		build();
	}
	
	void dicionario(){
		cout << "Dicionario:\n";
		for(auto [a, b]: code){
			if(to_string(a) == "10"){//quebra de linha
				std::cout << "|\\n| " << b << "\n";
				continue; 
			} 
			std::cout << "|" << a << "| " << b << "\n";
		}
		std::cout << "\n";
	}
	
	void codifica(std::string s){
		dfs(&root, "");                //desco ate o caracter
		                               //codifico e guardo a string codificada
		for(char k: s){
			CodText += code[k];
		}
	}
	void dfs(node **t, std::string path){
		if(!(*t)){       
			return;
		}
		if((*t)->leaf){                 //se for uma folha eu armazeno o caminho 
			code[(*t)->carac] = path;   
			return;
		}
		dfs(&((*t)->l), path+"0");      //construo o caminho, se eu for para
		dfs(&((*t)->r), path+"1");      //a esquerda adiciono 0 e para direita 1
	}
};
