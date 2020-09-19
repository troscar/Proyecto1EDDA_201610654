#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED
#include "NodoAlbum.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>



class Cubo
{
     public:
        NodoAlbum *root;
        Cubo()
        {
            root = new NodoAlbum("Mattriz","rojo");
            fila = root;
            columna = root;
            contador_x=(-1);
            contador_y=(-1);

        }

        
        int contador_x;
        NodoAlbum* buscar_columna(string X)
        {
            NodoAlbum *temp = root->getNext();
            while (temp != 0)
            {
                
                if (temp->getName().compare(X)==0)
                {
                    return temp;
                }
                temp = temp->getNext();
            }
            return 0;
        }


        int contador_y;
        NodoAlbum* buscar_fila(string Y )
        {
            NodoAlbum *temp = root->getDown();
            while(temp!=0)
            {
                if (temp->getName().compare(Y)==0)
                {
                    return temp;
                }
                temp = temp->getDown();
            }
            return 0;
        }
    // SOLO INGRESA EL NODO CABECERA DE DEL CUBO EN EL EJE DE LOS AÑOS CONECTADO CON LAS CABECERAS
    // SOLO UTILIZAR DESPUES DE COMPROBAR QUE NO EXISTEN 
        NodoAlbum* insertar_nueva_columna_ordenada(int x)
        {
            NodoAlbum *temp = root;
            while(temp->getNext()!=0){
                cout<<"buscando0";
                temp = temp->getNext();
            }
            cout<<"Termina";
            while (contador_x<x)
            {
                cout<<"crea";
                contador_x++;
                cout<<"crea1";
                NodoAlbum *nuevo = new NodoAlbum(to_string(contador_x),"blanco");
                cout<<"crea2";
                temp->setNext(nuevo);
                cout<<"crea3";
                temp = temp->getNext();
                cout<<"crea4";
            }
        }

        NodoAlbum* insertar_nueva_fila_ordenada(int y)
        {
            NodoAlbum *temp = root;
            while(temp->getDown()!=0){
                cout<<"buscando0";
                temp = temp->getDown();
            }
            cout<<"Termina";
            while (contador_y<y)
            {
                cout<<"crea";
                contador_y++;
                cout<<"crea1";
                NodoAlbum *nuevo = new NodoAlbum(to_string(contador_y),"blanco");
                cout<<"crea2";
                temp->setDown(nuevo);
                cout<<"crea3";
                temp = temp->getDown();
                cout<<"crea4";
            }
        }
/*
        void insertar_nodo_conectando(NodoAlbum * nuevo){
            NodoAlbum * columna = buscar_columna(nuevo->getX());
            NodoAlbum * fila = buscar_fila(nuevo->getMonth());

            // NO EXISTE NNGUN CABEZAL 
            if(fila==0 && columna==0){
                columna = insertar_nueva_columna_ordenada(nuevo->getYear());
                fila = insertar_nueva_fila_ordenada(nuevo->getMonth());
                fila->setNext(nuevo);
                columna->setDown(nuevo);
                nuevo->setBefore(fila);
                nuevo->setUp(columna);
                return;
            }

            //EXISTE EL AÑO PERO NO EL MES
            if(fila ==0 && columna!=0){
                bool antes = false;
                fila = insertar_nueva_fila_ordenada(nuevo->getMonth());
                while (columna->getDown()!=0){
                    if(columna->getMonth().compare(nuevo->getMonth()) == 1){
                        antes =true;
                        break;
                    }
                    columna = columna->getDown();
                }
                if(antes==true){
                    fila->setNext(nuevo);
                    columna->getUp()->setDown(nuevo);
                    nuevo->setBefore(fila);
                    nuevo->setUp(columna->getUp());
                    nuevo->setDown(columna);
                    columna->setUp(nuevo);
                    return;
                }
                if(antes==false){
                    fila->setNext(nuevo);
                    nuevo->setBefore(fila);
                    nuevo->setUp(columna);
                    columna->setDown(nuevo);
                    return;
                }
            }

            // EXISTE EL x PERO NO EL AÑO
            if(fila!=0 && columna==0){
                bool antes =false;
                columna = insertar_nueva_columna_ordenada(nuevo->getYear());
                while (fila->getNext()!=0){
                    if(fila->getYear().compare(nuevo->getYear()) == 1){
                        antes = true;
                        break;
                    }
                    fila = fila->getNext();
                }
                if(antes==true){
                    columna->setDown(nuevo);
                    fila->getBefore()->setNext(nuevo);
                    nuevo->setBefore(fila->getBefore());
                    nuevo->setNext(fila);
                    nuevo->setUp(columna);
                    fila->setBefore(nuevo);
                    return;
                }
                if(antes==false){
                    columna->setDown(nuevo);
                    nuevo->setUp(columna);
                    nuevo->setBefore(fila);
                    fila->setNext(nuevo);
                    return;
                }
            
            }


            // EXISTEN LOS DOS 
            if(fila!=0 && columna!=0){
                
            }
        }
        */
        void recorrer_cubo_en_colum(){
            NodoAlbum* auxFila = root;
            NodoAlbum* auxColu ;
            while (auxFila!=0)
            {
                cout <<"||" <<auxFila->getName() <<"||"<< endl;
                auxColu = auxFila; 
                while (auxColu != 0)
                {

                    cout <<"||" <<auxColu->getName() <<"||"<< endl;
                    auxColu = auxColu->getDown();
                }
                auxFila= auxFila->getNext();
                cout   << "-----fin columna-----"<<endl;
            }
            cout << "---------------------------------------------"<< endl;       
            cout << "---------FIN DE matriz -----------"<< endl;
        }

        void recorrer_cubo_en_fila(){
            NodoAlbum* auxFila ;
            NodoAlbum* auxColu = root;
            string nod;
            while (auxColu!=0)
            {
                auxFila = auxColu; 
                while (auxFila != 0)
                {   
                    cout <<"||" <<auxFila->getName() <<"||";
                    auxFila= auxFila->getNext();
                }
                auxColu= auxColu->getDown();
                cout   << "-----fin fila-----"<<endl;
            }
            cout << "---------------------------------------------"<< endl;       
            cout << "---------FIN DE matriz -----------"<< endl;      
        }


        NodoAlbum* buscar_nodo_(string nombre){
            NodoAlbum* auxFila = root;
            NodoAlbum* auxColu ;
            string nod;
            while (auxFila!=0)
            {
                auxColu = auxFila; 
                while (auxColu != 0)
                {
                    cout << nod << endl;
                    auxColu = auxColu->getDown();
                }
                auxFila= auxFila->getNext();
                cout   << "-----fin de la byusqueda-----"<<endl;
            }
            return 0;
        }
        string cuerpograph = "";
        void GRAficar(){
            cuerpograph ="";
            ofstream file;
            string str1 = "dot -Tpng Reportes\\archivoCubo.txt -o Reportes\\ReporteCubo.png";
            file.open("Reportes\\archivoCubo.txt");
            file << "digraph Sparce_Matrix{ \n" ;
            file << "node [shape=box]\n";
            file << "Mt [label = \"Matrix\" width = 1.5 style = filled, fillcolor = firebrick1];\n" ;

            file<<cuerpograph;
            file<<"}\n";
            file.close();
            system(str1.c_str());
            system("Reportes\\archivoCubo.png");
            cout << "------------------------ GRAFICADO ----------------------------";
        }

        private:
        NodoAlbum* fila;
        NodoAlbum* columna;

};
#endif //CUBO_H_INCLUDED