#pragma once
#include <iostream>
using namespace std;

class Nodo
{
public:
	string data;
	Nodo* Lchild; //hijo izquierdo
	Nodo* Rchild; //hijo derecho
	Nodo();
	~Nodo();
};