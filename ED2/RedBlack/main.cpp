#include <stdio.h>
#include <ctype.h>
#include <string>

#include "RBTree.h"

using namespace std;

int isValidItem();
void Menu();

int main()
{
	int item;
	RBTree tree;
	int opcao=-1;
	string op;

	while (1)
	{
		Menu();
		getline(cin,op);
		try
		{
			opcao=atoi(op.c_str());
			if (opcao > 0 && opcao <= 8)
			{
				switch (opcao)
				{
					case 1:	 item=isValidItem();
									 tree.insert(item);
									 break;
						
					case 2:	 tree.clearTree();
									 cout << "Tecle algo para continuar..." << endl;
									 cin.ignore();
									 break;
						
					case 3:  tree.dfs(1);//in
									 cout << "Tecle algo para continuar..." << endl;
									 cin.ignore();
									 break;
									 
					case 4:  tree.dfs(2);//pre
									 cout << "Tecle algo para continuar..." << endl;
									 cin.ignore();
									 break;
									 
					case 5:  tree.dfs(3);//pos
									 cout << "Tecle algo para continuar..." << endl;
									 cin.ignore();
									 break;

					case 6:	 tree.prettyPrint();
									 cout << "Tecle algo para continuar..." << endl;
									 cin.ignore();
									 break;
									 
					case 7:	 cout << tree.getN() << endl;
									 cout << "Tecle algo para continuar..." << endl;
									 cin.ignore();
									 break;
					case 8:  
									 return 0;

					default: throw op;
				}
			}
			else{
				throw op;
			}
		}
		catch (string op)
		{
			cout << endl << endl << "Opcao invalida: " << op << endl;
			cout << "Tecle algo para continuar..." << endl;
			cin.ignore();
		}
	}
}

void Menu(){
	cout << "  RedBlack   " << endl;
	cout << "  #############################################" << endl;
	cout << "  #                                           #" << endl;
	cout << "  #      [Selecione uma operacao]             #" << endl;
	cout << "  #                                           #" << endl;
	cout << "  #   1  - Insert Node                        #" << endl;
	cout << "  #   2  - Clear Tree                         #" << endl;
	cout << "  #   3  - Depth Search (In Order)            #" << endl;
	cout << "  #   4  - Depth Search (Pre Order)           #" << endl;
	cout << "  #   5  - Depth Search (Pos Order)           #" << endl;
	cout << "  #   6  - Print Tree                         #" << endl;
	cout << "  #   7  - Print Number of Nodes              #" << endl;
	cout << "  #   8  - Exit                               #" << endl;
	cout << "  #                                           #" << endl;
	cout << "  #############################################" << endl;
	cout << endl;
	cout << "Digite a opcao: ";
}

int isValidItem(){
	int item=-1;
	string strItem;

	while (1){
		cout << endl << "Digite um numero inteiro positivo : ";
		getline(cin, strItem);
		try
		{
			item=atoi(strItem.c_str());
			if (item>=0)
				return item;
			else
				throw strItem;
		}
		catch (string strItem)
		{
			cout << endl << endl << "Valor invalido: " << strItem << endl;
			cout << "Tecle algo para continuar..." << endl;
			cin.ignore();
		}
	}
}
