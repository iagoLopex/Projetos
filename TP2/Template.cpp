#include <bits/stdc++.h>

using namespace std;

////////////////////////////////////////////sum
template<typename T>
T sum(T total)
{
	return total;
}

template<typename T, typename... Args>
T sum(T inicio, Args... rest)
{
	return inicio + sum(rest...);
}

////////////////////////////////////////////print
void print(){}

template<typename T, typename... Args>
void print(T inicio, Args... rest)
{
	cout << inicio << endl;
	print(rest...);
}

////////////////////////////////////////////objeto com sobrecarga
template<typename T>
class Ex{

public:
	T soma =0;
	template<typename... rest>
	T func(T a, rest... B)     //se tem mais de um argumento
	{
		soma+=a;
		return func(B...);
	}
	template<typename... rest>
	T func(T x)                //se tem apenas um argumento
	{
		soma+=x;
		return soma;
	}
};

int main(){
	//string k = "asd";
	//string x = sum(k, k, k, k);
	//print(1,2,3,4);
	//Ex<int>calc;
	//cout << calc.func(1,1,3);
}
