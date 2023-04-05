#include <bits/stdc++.h>

using namespace std;

struct node{
	int v;
	node *left, *right;
	node(){
		v=0;
		left=right=0;
	}
};

class btree{
	
private:
	queue<node*>q;   //queue para insercao em largura
	node *root;
	int n;
	
public:
	btree(){
		root=0;
		n=0;
	}
	void insert(int x){
		node *aux = new node;
		aux->v = x;
		n++;
		if(!root){
			root = aux;
			q.push(root);
		}
		else{
			node *atual = q.front();
			if(atual->left){	   //se o left tem valor eu insiro na direita e tiro da fila
				atual->right = aux;
				q.push(aux);
				q.pop();
			}
			else{				   //senao insiro no left e nao tiro o elemento da fila
				atual->left = aux;
				q.push(aux);
			}
		}
	}
	int MaxSum(){
		
		int SumAt = -INT_MAX;
		
		if(n<3) return 0; //so existe uma folha
		
		auto dfs = [&](auto dfs, node* t) -> int{
			
			if(!(t->left) && !(t->right)) return (t->v); //se e folha eu retorno o valor
			
			int x = 0, y = 0;                      
			 x = dfs(dfs, t->left);   //guardo o valor do filho da esquerda
			 y = dfs(dfs, t->right);  //guardo o valor do filho da direita
			
			SumAt = max(SumAt, (t->v) + x + y);   //retorno a maior soma dessa sub-Arvore
			
			return (t->v + max(x,y));                            
		};
		
		dfs(dfs, root);
		
		return SumAt;
	}
};

int main(){
	
	btree tree;
	
	int o, k;
	cout << "Insira o numero de nodes:\n";
	cin>>o;
	cout << "Insira os nodes:\n";
	for(int i=0; i<o; i++){
		cin>>k;
		tree.insert(k);
	}
	cout << tree.MaxSum();
}
