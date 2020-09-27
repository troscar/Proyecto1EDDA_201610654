#ifndef NODOPROYECTO_H_INCLUDED
#define NODOPROYECTO_H_INCLUDED
#include <iostream>
#include <string>
#include "ArbolBB.h"
#include "Cubo.h"
using namespace std;

class NodoProyecto{
    public:
        Cubo *matriz;
        ArbolBB *arbolbb;
        NodoProyecto(int no_,string proyecto_,int nop_,string piso_)
        {
            no = no_;
            proyecto_ = proyecto_;
            nop=nop_;
            piso = piso_;
            matriz = new Cubo();
            arbolbb = new ArbolBB();
        }
        int getNo(){return no;}
        int getNop(){return nop;}
        string getProyecto() {return proyecto;}
        string getPiso() {return piso;}
        void setProyecto(string p) { proyecto = p;}
        void setPiso(string p) {piso = p;}
        
     private:
        int no;
        string proyecto;
        int nop;
        string piso;
        

};

#endif //NODOPROYECTO_H_INCLUDED