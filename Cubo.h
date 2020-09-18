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
        Cubo(string nombre)
        {
            root = new NodoAlbum(nombre,"","");
            fila = root;
            columna = root;

        }

        
        
        NodoAlbum* buscar_columna(string anyo)
        {
            NodoAlbum *temp = root->getNext();
            while (temp != 0)
            {
                
                if (temp->getName().compare(anyo)==0)
                {
                    return temp;
                }
                temp = temp->getNext();
            }
            return 0;
        }

        NodoAlbum* buscar_fila(string mes )
        {
            NodoAlbum *temp = root;
            while(temp!=0)
            {
                if (temp->getName().compare(mes)==0)
                {
                    return temp;
                }
                temp = temp->getDown();
            }
            return 0;
        }
    // SOLO INGRESA EL NODO CABECERA DE DEL CUBO EN EL EJE DE LOS AÑOS CONECTADO CON LAS CABECERAS
    // SOLO UTILIZAR DESPUES DE COMPROBAR QUE NO EXISTEN 
        NodoAlbum* insertar_nueva_columna_ordenada(string nuevo_anyo)
        {
            NodoAlbum *temp = root;
            bool   vacio = true;
            bool fin = false;
            if(root->getNext() != 0){
                vacio =false;
                temp = temp->getNext();
            }

            while (temp->getNext() != 0)
            {   
                
                if((temp->getName().compare(nuevo_anyo) == -1)){
                    if(temp->getNext()->getName().compare(nuevo_anyo) == 1){
                        NodoAlbum *nuevo = new NodoAlbum(nuevo_anyo,"","");
                        temp->getNext()->setBefore(nuevo);
                        nuevo->setBefore(temp);
                        nuevo->setNext(temp->getNext());
                        temp->setNext(nuevo);
                        return nuevo;
                    }
                }
                if(temp->getName().compare(nuevo_anyo)== 1){
                    if(temp->getBefore() == root){
                        NodoAlbum *nuevo = new NodoAlbum(nuevo_anyo,"","");
                        temp->getBefore()->setNext(nuevo);
                        nuevo->setBefore(temp->getBefore());
                        nuevo->setNext(temp);
                        temp->setBefore(nuevo);
                        return nuevo;  
                    }
                }
                temp = temp->getNext();      
                
            }

            if(vacio == true){
                NodoAlbum *nuevo = new NodoAlbum(nuevo_anyo,"","");
                root->setNext(nuevo);
                nuevo->setBefore(root);
                return nuevo;
            }
            if(vacio == false)
            {
                NodoAlbum *nuevo = new NodoAlbum(nuevo_anyo,"","");
                temp->setNext(nuevo);
                nuevo->setBefore(temp);
                return nuevo;
            }
        }

        NodoAlbum* insertar_nueva_fila_ordenada(string nuevo_mes)
        {
            NodoAlbum *temp = root;
            bool   vacio = true;
            if(root->getDown() != 0){
                vacio =false;
                temp = temp->getDown();
            }
            while (temp->getDown() != 0)
            {   
                if((temp->getName().compare(nuevo_mes) == -1)){
                    if(temp->getDown()->getName().compare(nuevo_mes) == 1){
                        NodoAlbum *nuevo = new NodoAlbum(nuevo_mes,"","");
                        temp->getDown()->setUp(nuevo);
                        nuevo->setUp(temp);
                        nuevo->setDown(temp->getDown());
                        temp->setDown(nuevo);
                        return nuevo;
                    } 
                }   
                if(temp->getName().compare(nuevo_mes)== 1){
                    if(temp->getUp() == root){
                        NodoAlbum *nuevo = new NodoAlbum(nuevo_mes,"","");
                        temp->getUp()->setDown(nuevo);
                        nuevo->setUp(temp->getUp());
                        nuevo->setDown(temp);
                        temp->setUp(nuevo);
                        return nuevo;  
                    }
                }    
                temp = temp->getDown();
            }

            if(vacio == true){
                NodoAlbum *nuevo = new NodoAlbum(nuevo_mes,"","");
                root->setDown(nuevo);
                nuevo->setUp(root);
                return nuevo;
            }
            if(vacio == false)
            {
                NodoAlbum *nuevo = new NodoAlbum(nuevo_mes,"","");
                temp->setDown(nuevo);
                nuevo->setUp(temp);
                return nuevo;
            }
        }

        void insertar_nodo_conectando(NodoAlbum * nuevo){
            NodoAlbum * columna = buscar_columna(nuevo->getYear());
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

            // EXISTE EL MES PERO NO EL AÑO
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
                bool existe = false;
                //BUSCO EL NODO EN LA INTERSECCION
                fila = fila->getNext();
                while (fila!=0){
                    if(fila->getYear().compare(nuevo->getYear()) == 0){
                        existe = true;
                        break;
                    }
                    fila = fila->getNext();
                }
                
                cout<< existe << endl;
                //cout<< fila->getName()<<fila->getYear()<<fila->getMonth() <<endl;
                //si hay un nodo en la posicion
                if(existe == true){
                    //cout<<"entro en el if"<<endl;
                    if(fila->getAde()==0){
                        fila->setAde(nuevo);
                        nuevo->setAtr(fila);
                        //cout<<"asignado encima"<<endl;
                        return;
                    }
                    if(fila->getAde()!=0){
                        while (true)
                        {
                            if(fila->getAde()==0){
                                break;
                            }
                            fila = fila->getAde();
                        }
                        fila->setAde(nuevo);
                        nuevo->setAtr(fila);
                        //cout<<"asignado encimafinal"<<endl;
                        return;
                        
                    }
                    //cout<< fila->getName()<<fila->getYear()<<fila->getMonth() <<endl;
                 
                }
                 //si el nodo no existe 
                 //FALTA VERIFICAR LOS NODOS ALREDEDOR SI EXISTEN               
                if(existe == false){
                    bool a = false;
                    bool b = false;
                    fila = buscar_fila(nuevo->getMonth());
                    columna = buscar_columna(nuevo->getYear());
                    string fi = fila->getName();
                    string  col = columna->getName();
                    //busco posicion mayor DE FILA
                    while (fila->getNext()!=0){
                        fila = fila->getNext();
                        if(fila->getYear().compare(nuevo->getYear()) == 1){
                            a = true;
                            break;
                        }
                    }
                    //BUSCO POSICION EN COLUMNA
                    while (columna->getDown()!=0){
                        columna = columna->getDown();
                        if(columna->getMonth().compare(nuevo->getMonth()) == 1){ 
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
            NodoAlbum* auxAde ;
            string nod;
            while (auxFila!=0)
            {
                auxColu = auxFila; 
                while (auxColu != 0)
                {
                    auxAde = auxColu->getAde();
                    nod = "";
                    nod = "|| " +auxColu->getName() + " " +auxColu->getYear() + " "+ auxColu->getMonth()+" || ";
                    while (auxAde != 0)
                    {
                        nod = nod + "|| " +auxAde->getName() + " " +auxAde->getYear() + " "+ auxAde->getMonth()+" || ";
                        auxAde = auxAde->getAde();
                    }
                    cout << nod << endl;
                    auxColu = auxColu->getDown();
                }
                auxFila= auxFila->getNext();
                cout   << "-----fin columna-----"<<endl;
            }
            cout << "---------------------------------------------"<< endl;       
            cout << "---------FIN DE album -----------"<< endl;
        }
        void recorrer_cubo_en_fila(){
            NodoAlbum* auxFila ;
            NodoAlbum* auxColu = root;
            NodoAlbum* auxAde;
            string nod;
            while (auxColu!=0)
            {
                auxFila = auxColu; 
                while (auxFila != 0)
                {   
                    auxAde = auxFila;
                    nod ="";
                    //nod = "|| " +auxFila->getName() + " " +auxFila->getYear() + " "+ auxFila->getMonth()+" || ";
                    while (auxAde != 0)
                    {
                        
                        nod = nod + "|| " +auxAde->getName() + " " +auxAde->getYear() + " "+ auxAde->getMonth()+" || ";
                        auxAde = auxAde->getAde();
                    }
                    cout << nod << endl;
                    
                    auxFila= auxFila->getNext();
                }
                auxColu= auxColu->getDown();
                cout   << "-----fin fila-----"<<endl;
            }
            cout << "---------------------------------------------"<< endl;       
            cout << "---------FIN DE album -----------"<< endl;      
        }


        NodoAlbum* buscar_nodo_(string nombre){
            NodoAlbum* auxFila = root;
            NodoAlbum* auxColu ;
            NodoAlbum* auxAde ;
            string nod;
            while (auxFila!=0)
            {
                auxColu = auxFila; 
                while (auxColu != 0)
                {
                    auxAde = auxColu;
                    while (auxAde->getAde() != 0)
                    {
                        if(auxAde->getName().compare(nombre)){
                            return auxAde;
                        }
                        auxAde = auxAde->getAde();
                    }
                    cout << nod << endl;
                    auxColu = auxColu->getDown();
                }
                auxFila= auxFila->getNext();
                cout   << "-----fin de la byusqueda-----"<<endl;
            }
            return 0;
        }

        void GRAficar(){
            ofstream file;
            file.open("C:/ruta/archivos/archivo.txt");
            file << "primera línea\n";
            file << "segunda línea\n";
            file << "tercera línea\n";
            file.close();

        }

        private:
        NodoAlbum* fila;
        NodoAlbum* columna;

};
#endif //CUBO_H_INCLUDED