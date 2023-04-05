#include <bits/stdc++.h>

using namespace std;

template<typename ty>
class node{
public:
	node<ty> *left, *right;
	int indice;
	ty v;
	
	node<ty>(ty k){
		left=right=nullptr;
		v=k;
	}
};


class tree{

private:
	map<char,bool>op;
	map<char,bool>pri;
	node<char> *root;
	int n;

public:
	tree(){
		op['*']=true;
		op['/']=true;
		op['+']=true;
		op['-']=true;
		
		pri['*']=true;
		pri['/']=true;
		
		root=0;
		n=0;
	}
	
	void build(string str){
		
		//constroi
		auto pref = [&](auto pref, int &ind) -> node<char>*{
			
			node<char> *aux = new node<char>(str[ind]);
			
			if(ind + 1 < (int)str.size()){
				
				if(op[str[ind]]){
					aux -> left = pref(pref, ++ind); 
					aux -> right = pref(pref, ++ind);
				}
			}
			return aux;
		};
		int start = 0;
		root = pref(pref, start);
		
		//imprime
		auto inf = [&](auto inf, node<char> *t) -> void{
			
			if(!t) return;

			if(pri[t->v])
				cout << "(";
			inf(inf, t->left);
			if(pri[t->v])
				cout << ")";
				
			cout << t->v;
			
			if(pri[t->v])
				cout << "(";
			inf(inf, t->right);
			if(pri[t->v])
				cout << ")";
			
		};
		inf(inf, root);
	}
};

int main(){
	
	tree a;
	string s;
	cin>>s;
	
	a.build(s);
}
