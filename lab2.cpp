

#include <iostream>
#include "Arbol.cpp"
#include "nodo.cpp"
using namespace std;
int main()
{
	string cad;
	cout << "Ingrese la cadena con las operaciones: " << endl;
	cin >> cad;
	Arbol arbol;
	arbol.create(cad, arbol.root);
	cout << "El resultado es: " << arbol.resolv_cadena(&arbol) << endl;
}

