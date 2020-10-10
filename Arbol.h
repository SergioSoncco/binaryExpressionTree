#pragma once
#include <iostream>
#include "Nodo.h"
using namespace std;
class Arbol
{
private:
public:
	Nodo* root;
	Arbol();
	Nodo* create(string cad, Nodo*);
	int resolv_cadena(Arbol*);
	int make_operations(Nodo*);
};