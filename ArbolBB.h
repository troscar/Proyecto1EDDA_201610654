#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
//#include "NodoArbol.h"
using namespace std;

class ArbolBB
{
    class Nodo{
        public:
            Nodo(string name_,string color_,string x_, string y_){
                izq = 0;
                der = 0;
                name =name_;
                color = color_;
                x=x_;
                y=y_;
            }
            Nodo *getIzq(){ return izq;}
            Nodo *getDer(){ return der;}
            string getName(){return name;}
            string getColor(){return color;}
            string getX(){return x;}
            string getY(){return y;}
            void setDer(Nodo* n){der = n;}
            void setIzq(Nodo* n){izq = n;}
            void PreOrdenGRAFICAR(Nodo *nodo, bool r);
            
            
        private:
        Nodo* izq;
        Nodo* der;
        string name;
        string color;
        string x;
        string y;

    };
    public: 
        
        ArbolBB(){
            root = 0;
        }  
        bool EstaVacio(){
            if(root!=0){
                return false;
            }else{
                return true;
            }
        }
        void insertar(string nom,string col,string x,string y){
            if(root!=0)
            {
                //cout<< root->getName()<<"||raiz|| agregar"<<endl;
                insertar_p(root,nom,col,x,y);//cout<<"vacio"<<endl;
            }
            else
            {
                Nodo *no = new Nodo(nom,col,x,y);
                root = no;
                //cout<< root->getName()<<"||raiz||"<<endl;
            }
            
        }
        void mostrar_arbol(){
            mostrar_arbol_p(root,0);
        }

        void PreOrdenGRAFICAR(Nodo *nodo, bool r){
        if(r){ 
            nodo = root;
            cuerpograph = cuerpograph + "{rank=same;"+nodo->getName()+";}";
        }


        MostrarGRAFICAR(nodo);
        if(nodo->getIzq()!=0){ PreOrdenGRAFICAR(nodo->getIzq(), false);}
        if(nodo->getDer()!=0) PreOrdenGRAFICAR(nodo->getDer(), false);
        }

        void MostrarGRAFICAR(Nodo *cabeza){
        cuerpograph = cuerpograph + "{rank=same;"+cabeza->getName()+";}\n";
        if((cabeza->getIzq()!=0)&&(cabeza->getDer()!=0)){
            cuerpograph = cuerpograph +"{rank=same;\""+cabeza->getIzq()->getName()+"\";\""+cabeza->getDer()->getName()+"\";} \n";
            cuerpograph = cuerpograph + "\""+cabeza->getName()+"\"->\""+cabeza->getIzq()->getName()+"\";\n";
            cuerpograph = cuerpograph + "\""+cabeza->getName()+"\"->\""+cabeza->getDer()->getName()+"\";\n";
        }
        if((cabeza->getIzq()==0)&&(cabeza->getDer()!=0)){
            cuerpograph = cuerpograph +"{rank=same;\""+cabeza->getDer()->getName()+"\";} \n";
            cuerpograph = cuerpograph + "\""+cabeza->getName()+"\"->\""+cabeza->getDer()->getName()+"\";\n";
        }
        if((cabeza->getIzq()!=0)&&(cabeza->getDer()==0)){
            cuerpograph = cuerpograph +"{rank=same;\""+cabeza->getIzq()->getName()+"\";} \n";
            cuerpograph = cuerpograph + "\""+cabeza->getName()+"\"->\""+cabeza->getIzq()->getName()+"\";\n";
        }
        
        }

        string cuerpograph="";
        void Graficar(){
            int q = 0 ;ofstream file;
            string cuerpo="",base ="";
            string str1 = "dot -Tpng Reportes\\ArbolBB.txt -o Reportes\\ArbolBB.png";
            file.open("Reportes\\ArbolBB.txt");
            file << "digraph G{ \n" ;
            file << "nodesep=0.8;\n";
            file << "ranksep=0.5;\n" ;
            PreOrdenGRAFICAR(NULL,true);
            file << cuerpograph;
            file <<"}\n";
            file.close();
            system(str1.c_str());
             cout << "------------------------ GRAFICADO ----------------------------";
            system("Reportes\\ArbolBB.png");
        }

    private:
         Nodo* root;
        
        void insertar_p(Nodo* raiz,string nam,string col,string x, string y){
            Nodo* noddo = new Nodo(nam,col,x,y);
            //cout<<"a";
            if(nam.compare(raiz->getName())== 1){
                if(raiz->getDer()!=0){
                    //cout<<"siguiente derecha\n";
                    insertar_p(raiz->getDer(),nam,col,x,y);
                    //cout<< "++1\n";
                    
                }else{
                    //cout<<"derre\n";
                    raiz->setDer(noddo);
                }
                
            }
            if(nam.compare(raiz->getName())== -1)
            {
                if(raiz->getIzq()!=0){
                    //cout<<"siguiente izquierda\n";
                    insertar_p(raiz->getIzq(),nam,col,x,y);
                    //cout<< "--1\n";
                }else{
                    //cout<<"izqq\n";
                    raiz->setIzq(noddo);
                }
                //cout<<"-1\n";
            }
            
        }
        
        void mostrar_arbol_p(Nodo* arbol,int contador){
            if(arbol !=0){
                mostrar_arbol_p(arbol->getIzq(),contador+1);
                
                cout << arbol->getName()<<endl;
                mostrar_arbol_p(arbol->getDer(),contador+1);
                
            }
        }



};
#endif //ARBOL_H_INCLUDED