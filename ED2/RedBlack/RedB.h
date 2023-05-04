#include <iostream>
#include <queue>

using namespace std;

struct Node {
	int key; 
	Node *parent; 
	Node *left; 
	Node *right;
	int color;
};

typedef Node *NodePtr;

class RedB {
private:
	Node* root;
	Node* LEAF;
	int n;

public:
	
	RedB() {
		LEAF = new Node;
		LEAF->color = 0;
		LEAF->left = nullptr;
		LEAF->right = nullptr;
		LEAF->parent = nullptr;
		root = LEAF;
		n=0;
	}
	
	int getN(){
		return n;
	}
	
	bool isEmpty(){
		return !n;
	}
	
	void clearTree()
	{
		//bfs pra deletar a arvore
		queue<Node*> fila;
		Node* p;
		if(!isEmpty()){
			fila.push(root);
			while(!fila.empty()){
				p = fila.front();
				fila.pop();

				if(p->left!=LEAF)
				{
					fila.push(p->left);
				}
				if(p->right!=LEAF)
				{
					fila.push(p->right);
				}
				delete p;
				n--;
			}
			root = LEAF;
		}
		else{
			cout << "Arvore vazia" << endl;
		}
	}
	
	void dfs(int x){
		if(!isEmpty()){
			if(x==1)
				inorder(root);
			if(x==2)
				preorder(root);
			if(x==3)
				posorder(root);
		}
		else{
			cout << "Arvore vazia\n";
		}
	}
	
	void preorder(Node* node){
		if (node == LEAF)
			return;
		cout<<node->key<<" color " << node->color << endl;
		preorder(node->left);
		preorder(node->right);
	}
	void inorder(Node* node){
		if (node == LEAF) 
			return;
		inorder(node->left);
		cout<<node->key<<" ";
		inorder(node->right);
	}
	void posorder(Node* node){
		if(node==LEAF) 
			return;
		posorder(node->left);
		posorder(node->right);
		cout<<node->key<<" ";
	}

	void fixInsert(Node * k)
	{
		Node* u;
		while (k->parent->color == 1) 
		{
			if (k->parent == k->parent->parent->right) { //se ele esta na direita
				u = k->parent->parent->left; 
				if (u->color == 1) { //se o tio, o pai e o node inserido forem vermelhos, eu apenas vou inverter as cores do pai, do tio e do avo 
					cout << "Case 3.1    (SubDireita)\n";
					cout << "o tio, o pai e o node inserido sao vermelhos, inverte as cores do pai, do tio e do avo\n\n";
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} 
				else 
				{
					if (k == k->parent->left) 
					{
						cout << "Case 3.2    (SubDireita)\n";
						cout << "o pai e o node inserido sao vermelhos, mas o tio é preto, rotacao a Direita\n\n";
						k = k->parent;
						RD(k);
					}
					cout << "Case 3.2    (SubDireita)\n";
					cout << "realizo rotacao para a Esquerda, apos a rotacao inverte a cor do pai e do avo\n\n";
					k->parent->color = 0;
					k->parent->parent->color = 1;
					RE(k->parent->parent);
				}
			} 
			else 
			{
				u = k->parent->parent->right;

				if (u->color == 1) 
				{
					cout << "Case 3.1    (SubEsquerda)\n";
					cout << "o tio, o pai e o node inserido sao vermelhos, inverte as cores do pai, do tio e do avo\n\n";
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} 
				else 
				{
					if (k == k->parent->right) 
					{
						cout << "Case 3.2    (SubEsquerda)\n";
						cout << "o pai e o node inserido sao vermelhos, mas o tio é preto, rotacao a Esquerda\n\n";
						k = k->parent;
						RE(k);
					}
					cout << "Case 3.2    (SubEsquerda)\n";
					cout << "realizo rotacao para a Direita, apos a rotacao inverte a cor do pai e do avo\n\n";
					k->parent->color = 0;
					k->parent->parent->color = 1;
					RD(k->parent->parent);
				}
			}
			if (k == root) 
			{
				break;
			}
		}
		root->color = 0;
	}
	
	/*------------------------------delete----------------------------------*/
		
	void fixDelete(Node* x) {
		Node* w;
		cout << "chama fix\n";
		while (x != root && x->color == 0) {
			if (x == x->parent->left){ //estou na esquerda
				w = x->parent->right;  //pego o irmao a direita
				
				if(w->color == 1){     //x preto,  w vermelho   ->  caso 3.1
					cout << "case 3.1    w é vermelho\n";
					w->color = 0;            //o irmao recebe preto
					x->parent->color = 1;    //o pai de ambos recebe vermelho
					RE(x->parent);           //x na esquerda e o w na direita, rotacao pra esquerda
					w = x->parent->right;    //o irmao atualiza(apos a rotacao o irmao muda)
				}

				if(w->left->color == 0 && w->right->color == 0){
					// case 3.2
					cout << "case 3.2    os filhos de w sao pretos\n";
					w->color = 1;
					x = x->parent;
				} 
				else{
					if(w->right->color == 0){
						// case 3.3
						cout << "case 3.3    os filhos de w sao pretos\n";
						w->left->color = 0;
						w->color = 1;
						RD(w);
						w = x->parent->right;
					}
					
					// case 3.4
					cout << "case 3.4    os filhos de w sao pretos\n";
					w->color = x->parent->color;
					x->parent->color = 0;
					w->right->color = 0;
					RE(x->parent);
					x = root;
				}
			} 
			else{
				w = x->parent->left;
				if (w->color == 1) {
					// case 3.1
					w->color = 0;
					x->parent->color = 1;
					RD(x->parent);
					w = x->parent->left;
				}

				if(w->right->color == 0 && w->right->color == 0){
					// case 3.2
					w->color = 1;
					x = x->parent;
				} 
				else{
					if(w->left->color == 0){
						// case 3.3
						w->right->color = 0;
						w->color = 1;
						RE(w);
						w = x->parent->left;
					}

					// case 3.4
					w->color = x->parent->color;
					x->parent->color = 0;
					w->left->color = 0;
					RD(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}
	
	Node* sucessor(Node* at){
		Node* aux = at;
		while(1){
			if(aux->left)
				aux = aux->left;
			else
				break;
		}
		return aux;
	}

	void Transplant(Node* u, Node* v){
		if (u->parent == nullptr) {
			root = v;
		} 
		else{
			if(u == u->parent->left)
				u->parent->left = v;
			else 
				u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void delet(int valor){
		Node* z = LEAF;
		Node* x, *y, *node=root;
		while (node != LEAF && z == LEAF){ //
			if (node->key == valor){
				z = node;
			}
			if(node->key <= valor)
				node = node->right;
			else
				node = node->left;
		}

		if (z == LEAF){
			cout<<"nao existe o valor na arvore"<<endl;
			return;
		}
		n--;
		
		y = z;
		int OriColor = y->color;
		if (z->left == LEAF){
			x = z->right;
			Transplant(z, z->right);
		}
		else{
			if (z->right == LEAF) {
				x = z->left;
				Transplant(z, z->left);
			} 
			else{//realizo a troca com o sucessor
				
				y = sucessor(z->right);
				OriColor = y->color; //o node que eu quero deletar agora tem a cor do sucessor
				x = y->right;        //como ele so tem a subarvore a direita eu preciso guardar ela
				if (y->parent == z){ 
					x->parent = y;
				}
				else{
					Transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				Transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
		}
		if (OriColor == 0){
			fixDelete(x);
		}
	}
	
	/*----------------------------------rotacao--------------------------------*/
	//rotacao a esquerda
	void RE(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != LEAF) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else{
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	//rotacao a direita
	void RD(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right != LEAF) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else
		{
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	
	/*----------------------------------insert--------------------------------*/
	void insert(int valor) {
		
		//inicializo o node a ser inserido com a cor vermelha
		Node* node = new Node;
		node->parent = nullptr;
		node->key = valor;
		node->left = LEAF;
		node->right = LEAF;
		node->color = 1; 
		n++;

		Node* pai = nullptr;
		Node* atual = this->root;
		
		while (atual != LEAF) {
			pai = atual;
			if (node->key < atual->key)
				atual = atual->left;
			else 
				atual = atual->right;
		}

		node->parent = pai;
		if (pai == nullptr) { //se o pai dele é null, ele é a a raiz 
			root = node;
		} 
		else{
			if (node->key < pai->key) 
				pai->left = node;
			else
				pai->right = node;
		}
		
		if (node->parent == nullptr){//caso o node inserido seja a raiz, o node recebe preto
			node->color = 0;
			return;
		}
		
		if (node->parent->parent == nullptr) //se o avo do node inserido for null apenas retorna 
			return;

		fixInsert(node); //senao conserta a arvore
	}

	void prettyPrint() {
		if(isEmpty()){
			cout << "Arvore vazia\n";
	    }
	    else{
			queue<Node*> fila;
			Node* p;
			fila.push(root);
			int i=0, pot=2;
			
			while(!fila.empty()){
				p = fila.front();
				fila.pop();
				
				cout << p->key;
				i++;
				cout << " \n"[i==pot-1];
				if(i == pot-1){
					pot*=2;
				}
				
				if(p->left!=LEAF)
				{
					fila.push(p->left);
				}
				if(p->right!=LEAF)
				{
					fila.push(p->right);
				}
			}
		}
	}
};
