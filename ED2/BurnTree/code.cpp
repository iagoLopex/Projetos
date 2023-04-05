#include <bits/stdc++.h>

using namespace std;

struct node{
	int v, index;
	node *left, *right, *father;
	node(){
		v=0;
		left=right=father=0;
	}
};

class btree{
	
private:
	queue<node*>q;                 //queue para insercao em largura
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
		aux->index = n+1;          //insiro um index unico para cada node
		n++;
		if(!root){
			root = aux;
			q.push(root);
		}
		else{
			
			node *atual = q.front();
			aux->father = atual;
			
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
	void burn(int value){
		
		node *aux = NULL;
		
		//busco o node desejado
		auto dfs = [&](auto dfs, node *t) -> void{
			
			if(!aux && t->v == value)
				aux = t;
				
			if(t->right)
				dfs(dfs, t->right);
			if(t->left)
				dfs(dfs, t->left);
		};
		dfs(dfs, root);
		
		if(!aux){
			cout << "Nao existe o node\n";
			return;
		}
		
		//inicio o processo de queima a partir do node desejado
		auto bfs = [&](auto bfs, node *t) -> void{
			
			queue<node*>q;
			
			q.push(t);
			while(!q.empty()){
				
				node *atual = q.front();
				q.pop();
				
				cout << atual->v << " ";
				
				if(atual->left){
					atual->left->father=NULL;
					q.push(atual->left);
				}
				if(atual->right){
					atual->right->father=NULL;    
					q.push(atual->right);
				}
				if(atual->father){
					if(atual->father->right->index == atual->index)  // o node de agora veio da direita do pai dele 
						atual->father->right = NULL;
					else                                             // senao o node de agora veio da esquerda do pai dele
						atual->father->left = NULL;	
					
					q.push(atual->father);
				}
				
				delete(atual);
			}
		};
		bfs(bfs, aux);
	}
};

int main(){
	
	btree tree;
	
	int o, k, start;
	cout << "Insira o numero de nodes:\n";
	cin>>o;
	cout << "Insira os nodes:\n";
	for(int i=0; i<o; i++){
		cin>>k;
		tree.insert(k);
	}
	
	cout << "Digite o node para iniciar a queima\n"; 
	cin>>start;
	tree.burn(start);
}
