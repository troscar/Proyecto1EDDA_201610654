#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
using namespace std;

#include "ArbolAvl.cpp"

int main()
{
   // Un �rbol de enteros
   AVL ArbolInt;

   // Inserci�n de nodos en �rbol:
   ArbolInt.Insertar("Oscar");
   ArbolInt.Insertar("Raul");
   ArbolInt.Insertar("Avila");
  /* ArbolInt.Insertar("Donado");
   ArbolInt.Insertar("Mynor");
   ArbolInt.Insertar("Ernesto");*/
   cout<< " . " <<endl;

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Mostrar el �rbol en tres ordenes distintos:
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;

   //ArbolInt.Borrar("Raul");

   cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

   // Mostrar el �rbol en tres ordenes distintos:
   cout << "InOrden: ";
   ArbolInt.InOrden(Mostrar);
   cout << endl;
   cout << "PreOrden: ";
   ArbolInt.PreOrden(Mostrar);
   cout << endl;
   cout << "PostOrden: ";
   ArbolInt.PostOrden(Mostrar);
   cout << endl;
   ArbolInt.Graficar();
   
    return 0;
}