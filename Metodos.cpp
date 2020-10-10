#include <string>
#include <iostream>
#include <vector>
#include "cabecera.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Retorna la info del nodo
std::string Node::getInfo(){
  return info;
}

//Cambia el valor de info del nodo
void Node::setInfo(std::string info){
  this->info = info;
}

/*
Retorna true si el nodo es operador(+ o *)
Retorna false si no lo es
*/
bool Node::isOperator(){
  if(info.compare("+")==0 | info.compare("*")==0){
    return true;
  }
  return false;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

double Sum::calculateSum(double a, double b){
  return a+b;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

double Multiplication::calculateMult(double a, double b){
  return a*b;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

/*
Metodo encargado de procesar una cadena del tipo "5+5*9+*9"
con operaciones de suma y multiplicacion, colocandolas en un vector de nodos
*/
void Interface::process(std::string exp, Core tree){
  unsigned int pos = 0;
  std::vector<Node> arrayNode;           //almacenara la expresion procesada
  while(pos<exp.length()){
    Node temp;                            //para almacenar el numero
    Node temp2;                           //para almacenar el operador
    unsigned int cut = pos;
    while(( !exp.substr(cut,1).compare("0") || !exp.substr(cut,1).compare("1") || !exp.substr(cut,1).compare("2") ||
            !exp.substr(cut,1).compare("3") || !exp.substr(cut,1).compare("4") || !exp.substr(cut,1).compare("5") ||
            !exp.substr(cut,1).compare("6") || !exp.substr(cut,1).compare("7") || !exp.substr(cut,1).compare("8") ||
            !exp.substr(cut,1).compare("9") || !exp.substr(cut,1).compare(".") ) && cut<exp.length()){
      cut++;
    }                                               //saber el tamaño del numero
    std::cout<<exp.substr(pos,(cut-pos));//imprimir el numero
    temp.setInfo(exp.substr(pos,(cut-pos)));        //cortar el numero
    arrayNode.push_back(temp);                      //ponerlo al final para evitar corromper el orden inicial
    if(!((cut+1)==exp.length())) {                  //si el que sigue es operador
      temp2.setInfo(exp.substr(cut,1));             //cortar ek operador
      std::cout<<exp.substr(cut,1);      //imprimir el operador
      arrayNode.push_back(temp2);                   //ponerlo al final para evitar corromper el orden inicial
    }
    pos = cut+1;                                    //pasamos al siguiente
  }
  arrayNode.pop_back();                            //siempre se genera uno adicional, lo sacamos
  tree.construct(arrayNode);                       //construimos el arbol
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

/*
Metodo para construir un arbol, de acuerdo a un vector
el operador siempre es numero impar, por lo cual anexa a ambos de su lado
si entra otro operador, si es suma, va hacia arriba, anexando al primer operador
si es multiplicacion, va hacia abajo, haciendo de que el ultimo operador lo anexe
*/
void Core::construct(std::vector<Node> exp){

  exp.at(1).sonLeft = &exp.at(0);            //construyendo un arbol inicial
  exp.at(1).sonRight = &exp.at(2);           //con los dos primeros numeros
  unsigned int pos = 3;
  unsigned int ultM = 1;
  unsigned int ultS = 1;
  while(pos<exp.size()){
    if(!exp.at(pos).getInfo().compare("+")){ //si entra suma
      exp.at(pos).sonLeft = &exp.at(ultS);   //anexamos la ultima suma
      exp.at(pos).sonRight = &exp.at(pos+1); //anexamos el operador
      ultS = pos;                            //actualizamos la posicion de la ultima suma
    }
    if(!exp.at(pos).getInfo().compare("*")){ //si entra multiplicacion
      exp.at(ultS).sonRight = &exp.at(pos);  //la ultima suma nos anexa
      exp.at(pos).sonLeft = &exp.at(pos-1);  //anexamos el operador anterior
      exp.at(pos).sonRight = &exp.at(pos+1); // anexamos el siguiente operador
      ultM = pos;
    }
    pos+=2;
  }
  std::cout<<std::endl<<"SIZE EXPRESSION: " + std::to_string(exp.size())<<std::endl; //imprimimos el tamaño, para verificar que no se perdio nada
  head = exp.at(ultS);                       //el head apunta a la cabeza del vector
  std::cout<<std::endl<<"-----PRINTING INORDER------"<<std::endl;
  inorder(&head);
  std::cout<<std::endl<<"-----ENDING INORDER--------"<<std::endl;
  std::cout<<"---------------------------"<<std::endl;
  std::cout<<"-----CALCULATING RESULT----"<<std::endl;
  std::cout<<"RESULT: "+ std::to_string(calculate(0, &exp.at(ultS)))<<std::endl; //mandamos a resolver
  std::cout<<"-----END-------------------"<<std::endl;

}
/*
Metodo que retorna el inorder de un arbol
*/
void Core::inorder(Node* node){
    if(node != nullptr){
      inorder(node->sonLeft);
      std::cout<<node->getInfo();
      inorder(node->sonRight);
    }
}

/*
Metodo que calcula el resultado de un arbol de expresion, que presenta los siguientes casos:

n ->* (numero y su hermano es multiplicacion)         --> calculado por recursividad
  ->+ (numero y su hermano es suma)                   --> calculado por recursividad
  ->n (numero y su hermano es numero)                 --> calculado directamente segun el operador padre
* ->* (multiplicacion y su hermano es multiplicacion) --> calculado por recursividad
  ->+ (multiplicacion y su hermano es suma)           --> calculado por recursividad
  ->n (multiplicacion y su hermano es numero)         --> calculado por recursividad
+ ->* (suma y su hermano es multiplicacion)           --> calculado por recursividad
  ->+ (suma y su hermano es suma)                     --> calculado por recursividad
  ->n (suma y su hermano es numero)                   --> calculado por recursividad
*/
double Core::calculate(double res, Node* node){
  Sum sum;
  Multiplication mult;
  if(!node->sonLeft->isOperator() && !node->sonRight->isOperator()){
    if(!node->getInfo().compare("+")){
      return(res += sum.calculateSum(std::stod(node->sonLeft->getInfo()),std::stod(node->sonRight->getInfo())));
    }
    else{
      return(res += mult.calculateMult(std::stod(node->sonLeft->getInfo()),std::stod(node->sonRight->getInfo())));
    }
  }
  else{
    if(node->sonLeft->isOperator() && !node->sonRight->isOperator()){
      if(!node->getInfo().compare("+")){
        return( sum.calculateSum(calculate(res, node->sonLeft),std::stod(node->sonRight->getInfo())) );
      }
      else{
        return( mult.calculateMult(calculate(res, node->sonLeft),std::stod(node->sonRight->getInfo())) );
      }
    }
    else if(!node->sonLeft->isOperator() && node->sonRight->isOperator()){
      if(!node->getInfo().compare("+")){
        return(res += sum.calculateSum(std::stod(node->sonLeft->getInfo()),calculate(res, node->sonRight)) );
      }
      else{
        return(res += mult.calculateMult(std::stod(node->sonLeft->getInfo()),calculate(res, node->sonRight)) );
      }
    }
    else if(node->sonLeft->isOperator() && node->sonRight->isOperator()){
      if(!node->getInfo().compare("+")){
        return( sum.calculateSum(calculate(res, node->sonLeft),calculate(res, node->sonRight)) );
      }
      else{
        return( mult.calculateMult(calculate(res, node->sonLeft),calculate(res, node->sonRight)) );
      }
    }
  }
  return res;
}
