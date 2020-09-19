#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
using namespace std;

class AVL;

// Clase Nodo de Arbol AVL:
class Nodo {
  public:
   // Constructor:
   Nodo(const string dat, Nodo *pad=NULL, Nodo *izq=NULL, Nodo *der=NULL) :
     dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
   // DATOS :
   string dato;
   int FE; //NUMERO DE FE
   Nodo *izquierdo;
   Nodo *derecho;
   Nodo *padre;
   friend class AVL;
};

class AVL {
  private:
   enum {IZQUIERDO, DERECHO};
   // Punteros de la lista, para cabeza y nodo actual:
   Nodo *raiz;
   Nodo *actual;
   int contador;
   int altura;

  public:
   // Constructor y destructor basicos:
   AVL() : raiz(NULL), actual(NULL) {}
   ~AVL() { Podar(raiz); }
   // Insertar en arbol ordenado:
   void Insertar(const string dat);
   // Borrar un elemento del �rbol:
   void Borrar(const string dat);
   // Funci�n de b�squeda:
   bool Buscar(const string dat);
   // Comprobar si el �rbol est� vac�o:
   bool Vacio(Nodo *r) { return r==NULL; }
   // Comprobar si es un nodo hoja:
   bool EsHoja(Nodo *r) { return !r->derecho && !r->izquierdo; }
   // Contar n�mero de nodos:
   const int NumeroNodos();
   const int AlturaArbol();
   // Calcular altura de un dato:
   int Altura(const string dat);
   // Devolver referencia al dato del nodo actual:
   string &ValorActual() { return actual->dato; }
   // Moverse al nodo raiz:
   void Raiz() { actual = raiz; }
   // Aplicar una funci�n a cada elemento del �rbol:
   void InOrden(void (*func)(string&, int) , Nodo *nodo=NULL, bool r=true);
   void InOrden2(void (*func)(string&, int) , Nodo *nodo=NULL, bool r=true);
   void PreOrden(void (*func)(string&, int) , Nodo *nodo=NULL, bool r=true);
   void PreOrdenGRAFICAR(Nodo *nodo=NULL, bool r=true);
   void PostOrden(void (*func)(string&, int) , Nodo *nodo=NULL, bool r=true);
   void Graficar();
   void MostrarGRAFICAR(Nodo *cabeza);
   void Listar_Arbol();
  private:
   // Funciones de equilibrado:
   void Equilibrar(Nodo *nodo, int, bool);
   void RSI(Nodo* nodo);
   void RSD(Nodo* nodo);
   void RDI(Nodo* nodo);
   void RDD(Nodo* nodo);
   // Funciones auxiliares
   void Podar(Nodo* &);
   void auxContador(Nodo*);
   void auxAltura(Nodo*, int);
};

// Poda: borrar todos los nodos a partir de uno, incluido
void AVL::Podar(Nodo* &nodo)
{
   // Algoritmo recursivo, recorrido en postorden
   if(nodo) {
      Podar(nodo->izquierdo); // Podar izquierdo
      Podar(nodo->derecho);   // Podar derecho
      delete nodo;            // Eliminar nodo
      nodo = NULL;
   }
}

// Insertar un dato en el �rbol AVL
void AVL::Insertar(const string dat)
{
   Nodo *padre = NULL;

   //cout << "Insertar: " << dat << endl;
   actual = raiz;
   // Buscar el dato en el �rbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && dat.compare(actual->dato)!=0) {
      padre = actual;
      if(dat.compare(actual->dato) == 1) actual = actual->derecho;
      else if(dat.compare(actual->dato) == -1) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual)) return;
   // Si padre es NULL, entonces el �rbol estaba vac�o, el nuevo nodo ser�
   // el nodo raiz
   if(Vacio(padre)) raiz = new Nodo(dat);
   // Si el dato es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(dat.compare(padre->dato) == -1) {
      padre->izquierdo = new Nodo(dat, padre);
      Equilibrar(padre, IZQUIERDO, true);
   }
   // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(dat > padre->dato) {
      padre->derecho = new Nodo(dat, padre);
      Equilibrar(padre, DERECHO, true);
   }
}

// Equilibrar �rbol AVL partiendo del nodo nuevo
void AVL::Equilibrar(Nodo *nodo, int rama, bool nuevo)
{
   bool salir = false;

   // Recorrer camino inverso actualizando valores de FE:
   while(nodo && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) nodo->FE--; // Depende de si a�adimos ...
         else                  nodo->FE++;
      else
         if(rama == IZQUIERDO) nodo->FE++; // ... o borramos
         else                  nodo->FE--;
      if(nodo->FE == 0) salir = true; // La altura de las rama que
                                      // empieza en nodo no ha variado,
                                      // salir de Equilibrar
      else if(nodo->FE == -2) { // Rotar a derechas y salir:
         if(nodo->izquierdo->FE == 1) RDD(nodo); // Rotaci�n doble
         else RSD(nodo);                         // Rotaci�n simple
         salir = true;
      }
      else if(nodo->FE == 2) {  // Rotar a izquierdas y salir:
         if(nodo->derecho->FE == -1) RDI(nodo); // Rotaci�n doble
         else RSI(nodo);                        // Rotaci�n simple
         salir = true;
      }
      if(nodo->padre) 
         if(nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
      nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
   }   
}

// Rotaci�n doble a derechas
void AVL::RDD(Nodo* nodo)
{
   cout << "RDD" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->izquierdo;
   Nodo *R = Q->derecho;
   Nodo *B = R->izquierdo;
   Nodo *C = R->derecho;

   if(Padre) 
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir �rbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

// Rotaci�n doble a izquierdas
void AVL::RDI(Nodo* nodo)
{
   cout << "RDI" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->derecho;
   Nodo *R = Q->izquierdo;
   Nodo *B = R->izquierdo;
   Nodo *C = R->derecho;

   if(Padre)
     if(Padre->derecho == nodo) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir �rbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

// Rotaci�n simple a derechas
void AVL::RSD(Nodo* nodo)
{
   cout << "RSD" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->izquierdo;
   Nodo *B = Q->derecho;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir �rbol:
   P->izquierdo = B;
   Q->derecho = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Rotaci�n simple a izquierdas
void AVL::RSI(Nodo* nodo)
{
   cout << "RSI" << endl;
   Nodo *Padre = nodo->padre;
   Nodo *P = nodo;
   Nodo *Q = P->derecho;
   Nodo *B = Q->izquierdo;

   if(Padre) 
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir �rbol:
   P->derecho = B;
   Q->izquierdo = P;
   
   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;
   
   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

// Eliminar un elemento de un �rbol AVL
void AVL::Borrar(const string dat)
{
   Nodo *padre = NULL;
   Nodo *nodo;
   string aux;

   actual = raiz;
   // Mientras sea posible que el valor est� en el �rbol
   while(!Vacio(actual)) {
      if(dat.compare(actual->dato)==0) { // Si el valor est� en el nodo actual
         if(EsHoja(actual)) { // Y si adem�s es un nodo hoja: lo borramos
            if(padre) // Si tiene padre (no es el nodo raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            delete actual; // Borrar el nodo
            actual = NULL;
            // El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
            // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
            if((padre->derecho == actual && padre->FE == 1) ||
               (padre->izquierdo == actual && padre->FE == -1)) {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }
            if(padre)
               if(padre->derecho == actual) Equilibrar(padre, DERECHO, false);
               else                         Equilibrar(padre, IZQUIERDO, false);
            return;
         }
         else { // Si el valor est� en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo m�s izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo m�s derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qu� ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que s�lo se eliminan nodos hoja.
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todav�a no hemos encontrado el valor, seguir busc�ndolo
         padre = actual;
         if(dat.compare(actual->dato)==1) actual = actual->derecho;
         else if(dat.compare(actual->dato)== -1) actual = actual->izquierdo;
      }
   }
}

// Recorrido de �rbol en inorden, aplicamos la funci�n func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::InOrden(void (*func)(string&, int) , Nodo *nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato, nodo->FE);
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}

// Recorrido de �rbol en preorden, aplicamos la funci�n func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::PreOrden(void (*func)(string&, int), Nodo *nodo, bool r)
{
   if(r) nodo = raiz;
   func(nodo->dato, nodo->FE);
   if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PreOrden(func, nodo->derecho, false);
}

// Recorrido de �rbol en postorden, aplicamos la funci�n func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::PostOrden(void (*func)(string&, int), Nodo *nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PostOrden(func, nodo->derecho, false);
   func(nodo->dato, nodo->FE);
}

// Buscar un valor en el �rbol
bool AVL::Buscar(const string dat)
{
   actual = raiz;

   // Todav�a puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat.compare(actual->dato)==0) return true; // dato encontrado
      else if(dat.compare(actual->dato)==1) actual = actual->derecho; // Seguir
      else if(dat.compare(actual->dato)==-1) actual = actual->izquierdo;
   }
   return false; // No est� en �rbol
}

// Calcular la altura del nodo que contiene el dato dat
int AVL::Altura(const string dat)
{
   int altura = 0;
   actual = raiz;

   // Todav�a puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat.compare(actual->dato)==0) return altura; // dato encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat.compare(actual->dato)==1) actual = actual->derecho;
         else if(dat.compare(actual->dato)==-1) actual = actual->izquierdo;
      }
   }
   return -1; // No est� en �rbol
}

// Contar el n�mero de nodos
const int AVL::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnci�n auxiliar
   return contador;
}

// Funci�n auxiliar para contar nodos. Funci�n recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void AVL::auxContador(Nodo *nodo)
{
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del �rbol, que es la altura del nodo de mayor altura.
const int AVL::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); // Funci�n auxiliar
   return altura;
}

// Funci�n auxiliar para calcular altura. Funci�n recursiva de recorrido en
// postorden, el proceso es actualizar la altura s�lo en nodos hojas de mayor
// altura de la m�xima actual
void AVL::auxAltura(Nodo *nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   // Proceso, si es un nodo hoja, y su altura es mayor que la actual del
   // �rbol, actualizamos la altura actual del �rbol
   if(EsHoja(nodo) && a > altura) altura = a;
}

// Funci�n de prueba para recorridos del �rbol
void Mostrar(string &d, int FE)
{
   cout << d << "(" << FE << "),";
}
int numeral=0;
void Mostrar2(string &d, int FE)
{
   numeral ++;
   cout << numeral << ". " << d << endl;
}

void AVL:: Listar_Arbol(){
   InOrden(Mostrar2);
   numeral=0;
}
string cuerpograph="";

void AVL::MostrarGRAFICAR(Nodo *cabeza){
   cuerpograph = cuerpograph + "{rank=same;"+cabeza->dato+";}\n";
   if((cabeza->izquierdo!=0)&&(cabeza->derecho!=0)){
      cuerpograph = cuerpograph +"{rank=same;\""+cabeza->izquierdo->dato+"\";\""+cabeza->derecho->dato+"\";} \n";
      cuerpograph = cuerpograph + "\""+cabeza->dato+"\"->\""+cabeza->izquierdo->dato+"\";\n";
      cuerpograph = cuerpograph + "\""+cabeza->dato+"\"->\""+cabeza->derecho->dato+"\";\n";
   }
   if((cabeza->izquierdo==0)&&(cabeza->derecho!=0)){
      cuerpograph = cuerpograph +"{rank=same;\""+cabeza->derecho->dato+"\";} \n";
      cuerpograph = cuerpograph + "\""+cabeza->dato+"\"->\""+cabeza->derecho->dato+"\";\n";
   }
   if((cabeza->izquierdo!=0)&&(cabeza->derecho==0)){
      cuerpograph = cuerpograph +"{rank=same;\""+cabeza->izquierdo->dato+"\";} \n";
      cuerpograph = cuerpograph + "\""+cabeza->dato+"\"->\""+cabeza->izquierdo->dato+"\";\n";
   }
   
}

void AVL::PreOrdenGRAFICAR(Nodo *nodo, bool r)
{
   if(r){ 
      nodo = raiz;
      cuerpograph = cuerpograph + "{rank=same;"+nodo->dato+";}";
   }


   MostrarGRAFICAR(nodo);
   if(nodo->izquierdo!=0){ PreOrdenGRAFICAR(nodo->izquierdo, false);}
   if(nodo->derecho!=0) PreOrdenGRAFICAR(nodo->derecho, false);
}

void AVL::Graficar(){
            int q = 0 ;ofstream file;
            string cuerpo="",base ="";
            string str1 = "dot -Tpng Reportes\\archivoARBOL.txt -o Reportes\\ReporteARBOL.png";
            file.open("Reportes\\archivoARBOL.txt");
            file << "digraph G{ \n" ;
            file << "nodesep=0.8;\n";
            file << "ranksep=0.5;\n" ;
            PreOrdenGRAFICAR(NULL,true);
            /*
            //file <<"{node[style=invis,label=""]; cx_30;\n}\n{node[style=invis, label="", width=.1]; ocx_45; ocx_20;\n}";
            ///NIVEL 0
            file <<"{rank=same;\"";
            file << raiz->dato;
            file << "\";}\n"; int d =0,d1=0;
            if(raiz->izquierdo!=0||raiz->derecho!=0){
                ///NIVEL 1
               
                if(raiz->izquierdo!=0){
                    file<< "\n{rank=same;";
                    file<<"\"" <<raiz->izquierdo->dato<< "\";";
                    cuerpo=cuerpo + "\""+raiz->dato+"\""+"->"+"\"" +raiz->izquierdo->dato+ "\";\n";
                    d=1;
                }
                if(raiz->derecho!=0){
                    if(d==0){
                        file<< "\n{rank=same;";
                    }
                    file<<"\"" <<raiz->derecho->dato<< "\";";
                    cuerpo=cuerpo+"\""+raiz->dato+"\""+"->" + "\""+raiz->derecho->dato+"\";\n";
                    if(raiz->derecho->izquierdo!=0 || raiz->derecho->derecho!=0){
                        d1=d1+2;
                    }
                }
                file<<"}\n";
                file<<cuerpo;
            }
            //cout<<"///////////////////////// fin NIVEL 1///////////////////////////////";
            /*cout<<d1;
            /////////NIVEL 2
            cuerpo ="";d=0;
            if(d1==1){
                file<< "\n{rank=same;";
                if(raiz->izquierdo->izquierdo!=0){
                    file<<"\"" <<raiz->izquierdo->izquierdo->dato<< "\";";
                    cuerpo=cuerpo + "\""+raiz->izquierdo->dato+"\""+"->"+"\"" +raiz->izquierdo->izquierdo->dato+ "\";\n";
                }
                if(raiz->izquierdo->derecho!=0){
                    file<<"\"" <<raiz->izquierdo->derecho->dato<< "\";";
                    cuerpo=cuerpo+"\""+raiz->izquierdo->dato+"\""+"->" + "\""+raiz->izquierdo->derecho->dato+"\";\n";
                }///----------------------------
            }
            if (d1==2){
                file<< "\n{rank=same;";
                if(raiz->derecho->izquierdo!=0){
                    file<<"\"" <<raiz->derecho->izquierdo->dato<< "\";";
                    cuerpo=cuerpo + "\""+raiz->izquierdo->dato+"\""+"->"+"\"" +raiz->izquierdo->izquierdo->dato+ "\";\n";
                }
                if(raiz->derecho->derecho!=0){
                    file<<"\"" <<raiz->derecho->derecho->dato<< "\";";
                    cuerpo=cuerpo+"\""+raiz->derecho->dato+"\""+"->" + "\""+ raiz->derecho->derecho->dato+"\";\n";
                }
            }
            if(d1==3){
                file<< "\n{rank=same;";
                if(raiz->izquierdo->izquierdo!=0){
                    file<<"\"" <<raiz->izquierdo->izquierdo->dato<< "\";";
                    cuerpo=cuerpo + "\""+raiz->izquierdo->dato+"\""+"->"+"\"" +raiz->izquierdo->izquierdo->dato+ "\";\n";
                }
                if(raiz->izquierdo->derecho!=0){
                    file<<"\"" <<raiz->izquierdo->derecho->dato<< "\";";
                    cuerpo=cuerpo+"\""+raiz->izquierdo->dato+"\""+"->" + "\""+raiz->izquierdo->derecho->dato+"\";\n";
                }
                if(raiz->derecho->izquierdo!=0){
                    file<<"\"" <<raiz->derecho->izquierdo->dato<< "\";";
                    cuerpo=cuerpo + "\""+raiz->izquierdo->dato+"\""+"->"+"\"" +raiz->izquierdo->izquierdo->dato+ "\";\n";
                }
                if(raiz->derecho->derecho!=0){
                    file<<"\"" <<raiz->derecho->derecho->dato<< "\";";
                    cuerpo=cuerpo+"\""+raiz->derecho->dato+"\""+"->" + "\""+raiz->derecho->derecho->dato+"\";\n";
                }
            }*/
            file<<cuerpograph;
            file<<"}\n";
            file.close();
            system(str1.c_str());
            cout << "------------------------ GRAFICADO ----------------------------";
            system("Reportes\\ReporteARBOL.png");
        }




