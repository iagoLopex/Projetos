#include <bits/stdc++.h>

#include "btree.h"
#include "node.h"

#define f first
#define s second

using namespace std;

int main(){
	
	tree huffman;
	char r;
	map<char, int>mp;
	priority_queue<pair<int,node*>, vector<pair<int, node*>>, greater<pair<int,node*>> >pq;
	
	//~ while(scanf("%c", &r)!=EOF){
		//~ mp[r]++;
		//~ huffman.OriText += r;
	//~ }
	
	////////////////////////////
	string str;
	getline(cin,str);
	for(char k: str){
		mp[k]++;
		str += k;
	}
	
	//insiro os primeiros nodes na fila
	for(auto [a, b]: mp){
		node *c = new node;
		c->leaf=1;
		c->freq=b;
		c->carac=a;
		pq.push({b, c});
	}
	
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
	
	//insiro o node que constitui a arvore na raiz
	huffman.root = pq.top().s;
	pq.pop();
	
	
	huffman.codifica(str);
	huffman.dicionario();
	cout << huffman.CodText << endl;
}
