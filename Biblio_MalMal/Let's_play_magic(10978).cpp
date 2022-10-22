#include <iostream>
#include "listDE.h"
#include "NodeD.h"
#include "Trem.h"
#include <vector>
#include <utility>

using namespace std;

int main(){
	
	NodeD<Trem>* start;
	string s1, s2;
	int n; cin>>n;
	Trem k;
	while(n){
		
		listDE<Trem>list;			
		vector<pair<string, int>>vec;
		for(int i=0; i<n; i++){
			
			cin >> s1 >> s2;
			k.ind=i;
			list.insert(k);
			vec.push_back({s1,s2.size()});
		}
		
		int cont, i=0;
		while(i<n){
			
			cont=vec[i].second;
			while(cont){
				if(list.it->x.ind == 0) start = list.it;
				if((list.it)->x.D == "@") cont--;
				list.itS();
			}
			list.itP();
			(list.it)->x.D = vec[i].first;
			
			i++;
		}
		for(int i=0; i<n; i++){
			
			list.itS();
		}
		list.it = start;
		cout << list.it->x.D;
		list.itS();
		for(int i=1; i<n; i++){
			cout << " "<< list.it->x.D;
			list.itS();
		}
		cout << endl;
		cin >> n;
	}
}
