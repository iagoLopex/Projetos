#include <bits/stdc++.h>

#include "btree.h"
#include "node.h"

#define f first
#define s second

using namespace std;

int main(){
	
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	
	char r;
	string s("");	
	while(scanf("%c", &r)!=EOF){
		s+=r;
	}
	huffman tree(s);
	
	tree.dicionario();
	cout << "Arquivo compactado:\n";
	cout << tree.CodText << endl;
}
