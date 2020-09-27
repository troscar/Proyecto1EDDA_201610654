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
#include "ListaDoble.h"
#include "NodoProyecto.h"
#include "NodoAlbum.h"

int Numero_Proyecto_Total;
int Numero_Proyecto_Pisos;
int Numero_Proyecto_Actual;
string Nombre_Proyecto_Actual;
string Nombre_Piso_Actual;
AVL ArbolP;
ListaDoble<NodoProyecto*> * Proyectos = new ListaDoble<NodoProyecto*>();
NodoProyecto *nuevo;NodoProyecto *temp;
graficas Grafi;
int main()
{
   
    int op =0;
    while (op != 7)
    {
        op=0;
        system("cls");
        Grafi.menu1();
        system("pause");
        Grafi.menu2();
        cin >> op;
        system("pause");
        switch(op)
		{
			case 1: 
                system("cls");
                int p;
                cout<< "---------- Proyectos ----------"<<endl;
                if(Proyectos->getSize()!=0){
                    int aux=0;int conta = 1;
                    while (aux<Proyectos->getSize())
                    {
                        if(Proyectos->get_element_at(aux)->getNo() == conta){
                            cout <<conta<<". " << Proyectos->get_element_at(aux)->getProyecto()<<endl;
                            conta++;
                        }
                        aux++;
                    }
                    cout<<"Ingrese numero de proyecto:"<< endl;
                    cin >>  p;
                    aux=0;
                    while (aux<Proyectos->getSize())
                    {
                        if(Proyectos->get_element_at(aux)->getNo() == p){
                            Nombre_Proyecto_Actual = Proyectos->get_element_at(aux)->getProyecto();
                            cout<< "Mostrar Piso:"<<Proyectos->get_element_at(aux)->getPiso() << "del proyecto " <<Proyectos->get_element_at(aux)->getProyecto()<<endl;
                            Proyectos->get_element_at(aux)->matriz->GRAficar();
                            system("pause");
                        }
                        aux++;
                    }
                }
                else{
                    cout<< " No tiene proyectos \n"<<endl;
                    system("pause");  
                } 
            break;
            case 2:
                //cout << "Has elejido 2.\n";
                system("cls");
                int p;
                cout<< "---------- Proyectos ----------"<<endl;
                if(Proyectos->getSize()!=0){
                    int aux=0;int conta = 1;
                    while (aux<Proyectos->getSize())
                    {
                        if(Proyectos->get_element_at(aux)->getNo() == conta){
                            cout <<conta<<". " << Proyectos->get_element_at(aux)->getProyecto()<<endl;
                            conta++;
                        }
                        aux++;
                    }
                    cout<<"Ingrese numero de proyecto:"<< endl;
                    cin >>  p;
                    aux=0;
                    while (aux<Proyectos->getSize())
                    {
                        if(Proyectos->get_element_at(aux)->getNo() == p){
                            Nombre_Proyecto_Actual = Proyectos->get_element_at(aux)->getProyecto();
                            Numero_Proyecto_Actual = Proyectos->get_element_at(aux)->getNo();
                        }
                        aux++;
                    }
                    
                    int op2;
                    int aux2;
                    while(op2!=5)
                    {
                        system("cls");
                        op2=0;
                        Grafi.menu3();
                        cin>> op2;
                        aux2=0;
                        switch(op2)
                        {
                            case 1:

                            break;
                            case 2:
                                cout << "NO Fue Implementado.\n";
                                system("pause");
                                break;
                            break;
                            case 3:
                                cout<< "---------- Pisos ----------"<<endl;
                                int eli;
                                while (aux<Proyectos->getSize())
                                {
                                    if(Proyectos->get_element_at(aux)->getProyecto().compare(Nombre_Proyecto_Actual)){
                                        cout <<Proyectos->get_element_at(aux)->getNop()<<". " << Proyectos->get_element_at(aux)->getPiso()<<endl;
                                        conta++;
                                    }
                                    aux++;
                                }
                                cout<<"Ingrese numero de piso:"<< endl;
                                cin >>  p;
                                Proyectos->remove_at(p);
                                cout<<"Piso Eliminado."<< endl;
                                system("pause");
                            break;
                            case 4:
                                while (aux<Proyectos->getSize())
                                {
                                    if(Proyectos->get_element_at(aux)->getNo()==(Numero_Proyecto_Actual)){
                                        Proyectos->remove_at(aux);
                                    }
                                    aux++;
                                }
                                cout<<"Proyecto Eliminado."<< endl;
                                system("pause");
                            break;
                            case 5:
                                cout << "Has elejido Volver.\n";
                                system("pause");
                                break;

                            break;
                            default:
                                cout << "Opcion default.\a\n";
                                system("pause");
                                break;
                        }
                        
                    }
                    system("pause");
                
                system("pause");
                break;
            case 3:
                cout << "Has elejido 3.\n";
                system("pause");
                break;
            case 4:
                int aux=0;int conta = 1;
                while (aux<Proyectos->getSize())
                {
                    if(Proyectos->get_element_at(aux)->getNo() == conta){
                        cout <<conta <<". " << Proyectos->get_element_at(aux)->getProyecto()<<endl;
                        ArbolP.Insertar(Proyectos->get_element_at(aux)->getProyecto());
                        conta++;
                    }
                    aux++;
                }
                ArbolP.Graficar();
                system("pause");
                break;
            case 5:
                cout << "Has elejido 5.\n";
                system("pause");
                break;
            case 6:
                cout << "Has elejido 6.\n";
                system("pause");
                break;
            case 7:
                cout << "Has elejido Salir.\n";
                system("pause");
                break;
            default:
                cout << "Opcion default.\a\n";
                system("pause");
                break;
        }
        
    }
    
    
    
    /*int q=0,h=0;
    //INGRESO DE LIBRERIA DE CANCIONES CARGA MASIVA INICIAL        
    cout << "---------------------------------------------"<< endl;
    cout << "---------------------------------------------"<< endl;
    using json = nlohmann::json;
    json j;
    std::ifstream reader("Library.json");
    reader >> j;
    for (const auto& librerys : j) {

         for (const auto& artistas : librerys) {
            //cout << "---------------------------------------------"<< endl;
            //cout << "------------------Artista--------------------"<< endl;
            string nameArtist =  artistas["Artist"]["Name"];
            //cout<< nameArtist << endl;
            string nameAlb = "";
            string nameMon =  "";
            string nameYear =  "";
            //Albummes = new Cubo(nameArtist);
            double ra = 0;
            double div1 = 0;
            double pro1 = 0;
            for (const auto& albumnes : artistas["Artist"]["Albums"]) {
                //cout << "------------------Album--------------------"<< endl;
                nameAlb =  albumnes["Name"];
                nameMon =  albumnes["Month"];
                nameYear =  albumnes["Year"];
               // Songgs = new Lista<NodoSong*>(); 
                double ran = 0;
                double div0 = 0; 
                double pro0 = 0;         
                //cout<< nameAlb << endl;    
                //cout<< nameMon << endl;    
                //cout<< nameYear << endl;   
                for(const auto& csnciones : albumnes["Songs"]){
                    //cout << "------------------Songs--------------------"<< endl;
                    string names =  csnciones["Name"];
                    string files =  csnciones["File"];
                    string ratin =  csnciones["Rating"];
                    //nodo0 = new NodoSong(names,files,stod(ratin));
                    //nodoaux = new NodoCancion(names,files,stod(ratin),nameAlb,nameArtist,nameYear,nameMon); 

                    h =0;
                    while (h<CAciones->getSize())
                    {
                        if(CAciones->get_element_at(h)->getName().compare(nodoaux->getName())==1){
                            CAciones->add_at(nodoaux,h);
                            //cout << "true"<<endl;
                            break;
                        }
                        //cout<<q<<nodoaux->getName()<<endl;
                        h++;
                    }
                    if(h==CAciones->getSize()){
                        CAciones->add_last(nodoaux);
                    }

                    ran = ran + stod(ratin); 
                    div0 ++;
                    //cout<< names << endl;    
                    //cout<< files << endl;    
                    //cout<< ratin << endl;   
                }
                //hacer el metodo recorrer para devolver el ranking promedio
                pro0 = ran / div0; 
                div1++;
                //nodo1 = new NodoAlbum(nameAlb,nameMon,nameYear,Songgs,pro0);
                //Albummes->insertar_nodo_conectando(nodo1);
                //nodoaux1= new NodoDisco(nameAlb,nameMon,nameYear,nameArtist,pro0);
            //----------------------------------//ORDENA LOS ALBUMNES//-----------------------------------------
                h =0;
                    while (h<DIscos->getSize())
                    {
                        if(DIscos->get_element_at(h)->getRating() <= nodoaux1->getRating()){
                            DIscos->add_at(nodoaux1,h);
                            
                            break;
                        }
                        //cout<<q<<nodoaux->getName()<<endl;
                        h++;
                    }
                    if(h==DIscos->getSize()){
                        DIscos->add_last(nodoaux1);
                    }
            //-------------------------------------------------------------------------------------
                ra = ra + pro0;
            }            
            //hacer el metodo recorrer para devolver el ranking promedio
            pro1 = ra / div1;
            nodo2= new NodoArtist(nameArtist,Albummes,pro1);

            q =0;
            while (q<Artisttas->getSize())
            {
                if(Artisttas->get_element_at(q)->getName().compare(nodo2->getName())==1){
                    Artisttas->add_at(nodo2,q);
                    //cout << "true"<<endl;
                    break;
                }
                //cout<<q<<nodo2->getName()<<endl;
                q++;
            }
            if(q==Artisttas->getSize()){
                Artisttas->add_last(nodo2);
            }
            q =0;
            while (q<CAntantes  ->getSize())
            {
                if(CAntantes->get_element_at(q)->getRating() <= nodo2->getRating()){
                    CAntantes->add_at(nodo2,q);
                    //cout << "true"<<endl;
                    break;
                }
                //cout<<q<<nodo2->getName()<<endl;
                q++;
            }
            if(q==CAntantes->getSize()){
                CAntantes->add_last(nodo2);
            }
        }    
    }
    reader.close();



    /*NodoProyecto *n = new NodoProyecto("0","0"); ;
    n->arbolbb->insertar("ma5","azul",0,0);
    n->arbolbb->insertar("ma12","azul",0,0);
    n->arbolbb->insertar("ma6","azul",0,0);
    n->arbolbb->insertar("ma1","azul",0,0);
    n->arbolbb->Graficar();
    NodoAlbum *nuevo = new NodoAlbum("cama1","azul",4,3);
    n->matriz->insertar_nodo_conectando(nuevo);
    n->matriz->GRAficar();*/
    return 0;
}



 /* graficas Graficar;
    Graficar.menu2(); */
    //PRUEBA DE MATRIZ
    /*Cubo *matriz = new Cubo();
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
*/
    
    

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

    //PRUEBA DE LISTA 
    /*ListaDoble<string> * Proy = new ListaDoble<string>();
    Proy->add_last("H");
    Proy->add_last("O");
    Proy->add_last("L");
    Proy->add_last("L");
    Proy->add_last("A");
    int aux=0;
    while (aux<Proy->getSize())
    {
        cout << Proy->get_element_at(aux)<<endl;
        aux++;
    }
    aux = 0 ;
    string te="";
    cout<<"1"<<endl;
    while (aux<Proy->getSize())
    {
        te = Proy->get_element_at(aux);
        if(te.compare("L")==0){
            Proy->remove_at(aux);
        }
        aux++;
    }
    aux=0;
    cout<< "2"<<endl;
     while (aux<Proy->getSize())
    {
        cout << Proy->get_element_at(aux)<<endl;
        aux++;
    }
    cout << "3"<<endl;*/
    