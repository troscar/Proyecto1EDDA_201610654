#ifndef GRAFICAS_H_INCLUDED
#define GRAFICAS_H_INCLUDED
#include <iostream>
using namespace std;
class graficas{

    public:
        graficas(){
        } 
        void menu1(){
        for(int i=0;i<50;i++){
            cout <<"*";
        }
        cout<<""<< endl;
        cout <<"* USAC ";
        for(int i=0;i<42;i++){
            cout <<" ";
        }
        cout <<"*";
        cout<<""<< endl;
        cout <<"* ESTRUCTURAS DE DATOS ";
        for(int i=0;i<26;i++){
            cout <<" ";
        }
        cout <<"*";
        cout<<""<< endl;
        cout <<"* SECCION A ";
        for(int i=0;i<37;i++){
            cout <<" ";
        }
        cout <<"*";
        cout<<""<< endl;
        cout <<"* OSCAR RAUL AVILA DONADO ";
        for(int i=0;i<23;i++){
            cout <<" ";
        }
        cout <<"*";
        cout<<""<< endl;
        cout <<"* 201610554 ";
        for(int i=0;i<37;i++){
            cout <<" ";
        }
        cout <<"*";
        cout<<""<< endl;
        for(int i=0;i<50;i++){
            cout <<"*";
        }
        cout<<""<< endl; 
    }
        void menu2(){
        cout <<"---------------------------------------------"<< endl;
        cout <<"--------------------MENU---------------------"<< endl;
        cout <<"---------------------------------------------"<< endl;
        cout <<"1. Ver Proyectos "<< endl;
        cout <<"2. Editar Proyectos"<<endl;
        cout <<"3. Cargar Proyecto "<<endl;
        cout <<"4. Graficar Proyectos"<<endl;
        cout <<"5. Guardar Proyectos"<<endl;
        cout <<"6. Cargar Librerias" <<endl;   
        
    }

    
};

#endif //GRAFICAS_H_INCLUDED