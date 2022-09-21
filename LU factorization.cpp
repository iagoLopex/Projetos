#include <bits/stdc++.h>

using namespace std;

int main(){
	cout<<fixed<<setprecision(5);
    int n; cin>>n;
    queue<double>constantes;
    double A[n][n],B[n],L[n][n],U[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>A[i][j];
            U[i][j]=A[i][j];
        }
    }
    for(int i=0; i<n; i++){
        cin>>B[i];
    }
    //Calculando a matriz U, e determinando as constantes para formar a matriz L
    for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i>j){
				constantes.push(U[i][j]/U[j][j]);
				for(int k=j; k<n; k++){
					U[i][k]=A[i][k]-A[j][k]*(A[i][j]/A[j][j]);
				}
			}
		}
	}
	//Calculando a matriz L, a partir das constantes calculadas
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j) L[i][j]=1;
            else{
                if(i<j) L[i][j]=0;
                else{
                    L[i][j]=constantes.front(); constantes.pop();
                }
            }
        }
    }
    vector<double>Y,X;
    Y.emplace_back(B[0]);
    for(int i=1; i<n; i++){
        double soma=0;
        for(int j=0; j<i; j++){
            soma+=(L[i][j]*Y[j]);
        }
        Y.emplace_back(B[i]-soma);
    }
    X.emplace_back(Y[n-1]/U[n-1][n-1]);
    for(int i=n-2,k=0; i>=0; i--){
		double soma=0;
		for(int j=n-1; j>=0; j--){
			if(i==j){
				X.emplace_back(soma/U[i][j]*-1);//talvez de errado
				k++;
			}
			else if(j>i){
				soma+=(U[i][j]*X[k]-Y[k]);
			}
		}
	}
    cout<<"Valores de Y: "<<endl;
    for(int i=0; i<(int)Y.size(); i++){
        cout<<Y[i]<<endl;
    }
    cout<<"Valores de X: "<<endl;
    for(int i=0; i<(int)X.size(); i++){
		cout<<X[i]<<endl;
	}   
    cout<<"Matriz L: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<L[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<"Matriz U: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<U[i][j]<<' ';
        }
        cout<<endl;
    }
}
