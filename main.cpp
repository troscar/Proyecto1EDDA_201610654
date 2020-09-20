#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "json/json.hpp"
using namespace std;
using json = nlohmann::json;

#include "ArbolAvl.cpp"
#include "ArbolBB.h"
#include "graficas.h"
#include "Cubo.h"

int main()
{
    Cubo *matriz = new Cubo();
    NodoAlbum *nuevo = new NodoAlbum("cama1","azul",4,3);
    matriz->insertar_nodo_conectando(nuevo);
    nuevo = new NodoAlbum("cama2","azul",4,6);
    matriz->insertar_nodo_conectando(nuevo);
    nuevo = new NodoAlbum("cama3","azul",7,8);
    matriz->insertar_nodo_conectando(nuevo);
    nuevo = new NodoAlbum("cama4","azul",12,8);
    matriz->insertar_nodo_conectando(nuevo);
    nuevo = new NodoAlbum("cama6","azul",0,0);
    matriz->insertar_nodo_conectando(nuevo);
    //matriz->insertar_nueva_columna_ordenada(12);
    //matriz->insertar_nueva_fila_ordenada(6);
    matriz->recorrer_cubo_en_fila();
    //matriz->recorrer_cubo_en_colum();
    matriz->GRAficar();

    
    return 0;
}
 /* graficas Graficar;
    Graficar.menu2(); */

    //PRUEBA ARBOLL AVL 
   /*AVL ArbolS;

   // Inserci�n de nodos en �rbol:
   ArbolS.Insertar("Oscar");
   ArbolS.Insertar("Raul");
   ArbolS.Insertar("Avila");
   ArbolS.Insertar("Donado");
   ArbolS.Insertar("Mynor");
   ArbolS.Insertar("Ernesto");
   cout<< " . " <<endl;

   cout << "Altura de arbol " << ArbolS.AlturaArbol() << endl;

   // Mostrar el �rbol en tres ordenes distintos:
   ArbolS.Listar_Arbol();
   ArbolS.Listar_Arbol();
   }*/

    //PRUEBA ARBOL BB
  
    /*ArbolBB ABB;
    ABB.insertar("nnn","azul","12","15");
    ABB.insertar("uuu","azul","12","15");
    ABB.insertar("ccc","azul","12","15");
    ABB.insertar("ddd","azul","12","15");
    ABB.insertar("lll","azul","12","15");
    ABB.insertar("kkk","azul","12","15");
    ABB.insertar("aaa","azul","12","15");
    ABB.insertar("mmm","azul","12","15");
    ABB.insertar("ttt","azul","12","15");
    ABB.insertar("zzz","azul","12","15");
    ABB.Graficar();
    ABB.mostrar_arbol();*/
