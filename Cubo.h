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
                temp = temp->getNext();
            }
            while (contador_x<x)
            {
                contador_x++;
                NodoAlbum *nuevo = new NodoAlbum(to_string(contador_x),"blanco",contador_x,-1);
                temp->setNext(nuevo);
                temp = temp->getNext();
            }
            return temp;
        }

        NodoAlbum* insertar_nueva_fila_ordenada(int y)
        {
            NodoAlbum *temp = root;
            while(temp->getDown()!=0){
                temp = temp->getDown();
            }
            while (contador_y<y)
            {
                contador_y++;
                NodoAlbum *nuevo = new NodoAlbum(to_string(contador_y),"blanco",-1,contador_y);
                temp->setDown(nuevo);
                temp = temp->getDown();
            }
            return temp;
        }

        void insertar_nodo_conectando(NodoAlbum * nuevo){
            NodoAlbum * columna = buscar_columna(to_string(nuevo->getX()));
            NodoAlbum * fila = buscar_fila(to_string(nuevo->getY()));

            // NO EXISTE NNGUN CABEZALES 
            if(fila==0 && columna==0){
                columna = insertar_nueva_columna_ordenada(nuevo->getX());
                fila = insertar_nueva_fila_ordenada(nuevo->getY());
                fila->setNext(nuevo);
                columna->setDown(nuevo);
                nuevo->setBefore(fila);
                nuevo->setUp(columna);
                return;
            }

            //EXISTE EL x PERO NO Y
            if(fila ==0 && columna!=0){
                bool antes = false;
                fila = insertar_nueva_fila_ordenada(nuevo->getY());
                while (columna->getDown()!=0){
                    if(to_string(columna->getY()).compare(to_string(nuevo->getY())) == 1){
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

            // EXISTE EL Y PERO NO  X
            if(fila!=0 && columna==0){
                bool antes =false;
                columna = insertar_nueva_columna_ordenada(nuevo->getX());
                while (fila->getNext()!=0){
                    if(to_string(fila->getX()).compare(to_string(nuevo->getX())) == 1){
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
                bool existe = false;
                //BUSCO EL NODO EN LA INTERSECCION
                fila = fila->getNext();
                while (fila!=0){
                    if(to_string(fila->getX()).compare(to_string(nuevo->getX())) == 0){
                        existe = true;
                        break;
                    }
                    fila = fila->getNext();
                }
                 //si el nodo no existe 
                 //FALTA VERIFICAR LOS NODOS ALREDEDOR SI EXISTEN               
                if(existe == false){
                    bool a = false;
                    bool b = false;
                    fila = buscar_fila(to_string(nuevo->getY()));
                    columna = buscar_columna(to_string(nuevo->getX()));
                    string fi = fila->getName();
                    string  col = columna->getName();
                    //busco posicion mayor DE FILA
                    while (fila->getNext()!=0){
                        fila = fila->getNext();
                        if(to_string(fila->getX()).compare(to_string(nuevo->getX())) == 1){
                            a = true;
                            break;
                        }
                    }
                    //BUSCO POSICION EN COLUMNA
                    while (columna->getDown()!=0){
                        columna = columna->getDown();
                        if(to_string(columna->getY()).compare(to_string(nuevo->getY())) == 1){ 
                            b = true;
                            break;
                        }
                    }
                    //existe dentro del marco de < mes y < anyo
                    if(a == true && b == true){
                        nuevo->setUp(columna->getUp());
                        nuevo->setDown(columna);
                        nuevo->setBefore(fila->getBefore());
                        nuevo->setNext(fila);
                        columna->getUp()->setDown(nuevo);
                        columna->setUp(nuevo);
                        fila->getBefore()->setNext(nuevo);
                        fila->setBefore(nuevo);
                    }
                    //existe en el dentro de mes pero no de anyo
                    if(a == true && b == false){
                        nuevo->setUp(columna);
                        nuevo->setBefore(fila->getBefore());
                        nuevo->setNext(fila);
                        columna->setDown(nuevo);
                        fila->getBefore()->setNext(nuevo);
                        fila->setBefore(nuevo);
                    
                    }
                    //existe en dentro de anio pero no de mes 
                    if(a == false && b == true){
                        nuevo->setUp(columna->getUp());
                        nuevo->setDown(columna);
                        nuevo->setBefore(fila);
                        fila->setNext(nuevo);
                        columna->getUp()->setDown(nuevo);
                        columna->setUp(nuevo);
                    
                    }
                    //existe fuera del cuadro
                    if(a == false && b == false){
                        nuevo->setUp(columna);
                        nuevo->setBefore(fila);
                        fila->setNext(nuevo);
                        columna->setDown(nuevo);
                    
                    }
                }   
            }
        }


        void recorrer_cubo_en_colum(){
            NodoAlbum* auxFila = root;
            NodoAlbum* auxColu ;
            while (auxFila!=0)
            {
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
        
        string cuerpograph = "";
        void GRAficar(){
            cuerpograph ="";
                ofstream file;
                string str1 = "dot -Tpng Reportes\\archivoCubo.txt -o Reportes\\ReporteCubo.png";
                file.open("Reportes\\archivoCubo.txt");
                file << "digraph Sparce_Matrix{ \n" ;
                file << "node [shape=box]\n";
                file << "Mt [label = \"Matrix\" width = 1.5 style = filled, fillcolor = firebrick1];\n" ;

                NodoAlbum* temp = root->getDown();
                int contax=-1;
                while(temp!=0){
                    contax++;
                    cuerpograph = cuerpograph + "U"+to_string(contax)+" [label = \""+temp->getName()+"\" pos = \"5.3,3.5!\"width = 1.5 style = filled];\n";
                    temp = temp->getDown();
                }
                if(contax>-1){
                    cuerpograph = cuerpograph + "Mt -> U0;\n";
                }
                for(int i=0;i<contax;i++){
                    cuerpograph = cuerpograph + "U"+to_string(i)+" -> U"+to_string(i+1)+" { constraint = true };\n"; 
                }

                temp = root->getNext();
                int contay=-1;
                while(temp!=0){
                    contay++;
                    cuerpograph = cuerpograph + "A"+to_string(contay)+" [label = \""+temp->getName()+"\" width = 1.5 style = filled];\n";
                    temp = temp->getNext();
                }
                if(contay>-1){
                    cuerpograph = cuerpograph + "Mt -> A0 { constraint = true };\n";
                }
                for(int i=0;i<contay;i++){
                    cuerpograph = cuerpograph + "A"+to_string(i)+" -> A"+to_string(i+1)+";\n"; 
                }
                cuerpograph = cuerpograph + "{ rank = same; Mt; ";
                for(int i=0;i<contay+1;i++){
                    cuerpograph = cuerpograph + "A"+to_string(i)+" ;"; 
                }
                cuerpograph = cuerpograph + " }\n";
                cout<< contax <<endl;
                cout<< contay <<endl;
                NodoAlbum* auxFila = root->getDown();
                NodoAlbum* auxColu ;
                int cx=0 ; int cy=0;
                int cabezalx = (-1); int cabezaly =(-1);
                string cue="";string cuey="";
                bool agre = false;
                while (auxFila!=0)
                {
                    auxColu = auxFila->getNext(); 
                    agre = false;
                    cabezalx=(-1);
                    while(auxColu!=0){
                        cuerpograph = cuerpograph + "N"+to_string(auxColu->getX())+"_L"+ to_string(auxColu->getY())+" [label = \""+auxColu->getName()+"\" width = 1.5];\n";
                        cx=auxColu->getX();
                        cue = cue + "N"+to_string(auxColu->getX())+"_L"+ to_string(auxColu->getY())+";";
                        if(cabezalx==(-1)){
                            cuerpograph = cuerpograph + "U"+to_string(auxFila->getY()) +" -> N"+to_string(auxColu->getX())+"_L"+ to_string(auxColu->getY())+"\n";
                            cabezalx = auxColu->getX();
                        }if(cabezalx!=(-1)){
                            cuerpograph = cuerpograph + "N"+to_string(cabezalx)+"_L"+ to_string(auxColu->getY()) +" -> N"+to_string(auxColu->getX())+"_L"+ to_string(auxColu->getY())+"\n";
                            cabezalx = auxColu->getX();
                        } 
                        auxColu = auxColu->getNext();
                        agre = true;
                    }
                    if(agre){
                        cuerpograph = cuerpograph+ "{ rank = same; U"+to_string(auxFila->getY()) +";"+cue+"  }\n";
                        cue="";
                    }
                    auxFila= auxFila->getDown();
                }
               auxFila ;
                 auxColu = root->getNext();
                 cx=0 ;  cy=0;
                 cabezalx = (-1);  cabezaly =(-1);
                 cue="";
                 agre = false;
                while (auxColu!=0)
                {
                    auxFila = auxColu->getDown();
                    agre = false;
                    cabezaly=(-1); 
                    while (auxFila != 0)
                    {   
                        cue = cue + "N"+to_string(auxFila->getY())+"_L"+ to_string(auxFila->getX())+";";
                        if(cabezaly==(-1)){
                            cuerpograph = cuerpograph + "A"+to_string(auxColu->getX()) +" -> N"+to_string(auxColu->getX())+"_L"+ to_string(auxFila->getY())+"\n";
                            cabezaly = auxFila->getY();
                        }if(cabezaly!=(-1)){
                            cuerpograph = cuerpograph + "N"+to_string(auxColu->getX())+"_L"+ to_string(cabezaly) +" -> N"+to_string(auxColu->getX())+"_L"+ to_string(auxFila->getY())+"\n";
                            cabezaly = auxFila->getY();
                        } 
                        auxFila= auxFila->getDown();
                        //agre = true;
                    }
                    if(agre){
                        cuerpograph = cuerpograph+ "{ rank = same; A"+to_string(auxColu->getX()) +";"+cue+"  }\n";
                        cue="";
                    }
                    auxColu= auxColu->getNext();

                }



                file<<cuerpograph;
                file<<"}\n";
                file.close();
                system(str1.c_str());
                system("Reportes\\ReporteCubo.png");
                cout << "------------------------ GRAFICADO ----------------------------";            
        }

        private:
        NodoAlbum* fila;
        NodoAlbum* columna;

};
#endif //CUBO_H_INCLUDED