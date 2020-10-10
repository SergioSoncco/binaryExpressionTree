#include "Arbol.h"

Arbol::Arbol()
{
	this->root = new Nodo;
}

Nodo* Arbol::create(string cad, Nodo* p)
{

	if (cad.find("+") == string::npos)
	{
		if (cad.find("*") == string::npos) //Hemos llegado al final ya no hay may operaciones asi que solo quedan numeros
		{
			p->data = cad; //pondra la cada como el dato del nodo sin importar cuantas cifras tengan puesta que ya solo quedan numeros
			p->Lchild = NULL;//No tendra hijos
			p->Rchild = NULL;
		}
		else //Entrara aqui porque no encontro suma pero  si multiplicacion
		{
			p->data = ("*"); //Pondra el simbolo de multiplicacion en el dato del nodo
			p->Lchild = new Nodo;
			p->Rchild = new Nodo;
			p->Lchild = create(cad.substr(0, cad.find("*")), p->Lchild); // Partira la cadena a partir del simbolo y le pasara la izquierda al hijo izquierdo del nodo p
			p->Rchild = create(cad.substr(cad.find("*") + 1, cad.length() - cad.find("*")), p->Rchild); // Le pasara la parte derecha de la cadena al nodo derecho del nodo p

		}
	}
	else  // entrara aqui en cado encuentra una operacion de suma
	{
		p->data = ("+"); //Pondra el simbolo de suma en el dato del nodo
		p->Lchild = new Nodo;
		p->Rchild = new Nodo;
		p->Lchild = create(cad.substr(0, cad.find("+")), p->Lchild);  // Partira la cadena a partir del simbolo y le pasara la izquierda al hijo izquierdo del nodo p
		p->Rchild = create(cad.substr(cad.find("+") + 1, cad.length() - cad.find("+")), p->Rchild); // Le pasara la parte derecha de la cadena al nodo derecho del nodo p
	}
	return p;
}
int Arbol::resolv_cadena(Arbol* a)
{
	return make_operations(a->root);
}
int Arbol::make_operations(Nodo* p)
{
	if (p->data.compare("+") == 0)
	{
		return make_operations(p->Lchild) + make_operations(p->Rchild);
	}
	else
	{
		if (p->data.compare("*") == 0)
		{
			return make_operations(p->Lchild) * make_operations(p->Rchild);
		}
		else
		{
			return atoi(p->data.c_str());
		}
	}

}

void Arbol::inorder(Nodo* node){
    if(node != nullptr){
      inorder(node->Lchild);
      std::cout<<node->data;
      inorder(node->Rchild);
    }
}

void Arbol::delete_tree(Nodo* node){
	if(node != nullptr){
		delete_tree(node->Lchild);
		delete_tree(node->Rchild);
		std::cout<<"deleted ";
		delete node;
	}
}
