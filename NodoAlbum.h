#ifndef NODOALBUM_H_INCLUDE
#define NODOALBUM_H_INCLUDE
#include <iostream>
#include <string>
using namespace std;

class NodoAlbum{
    public:
        NodoAlbum(string name_,string color_)
        {
            name = name_;
            color = color_;
            x = -1;
            y = -1;
            

            next = 0;
            before = 0;
            up  = 0;
            down = 0; 
        }
        NodoAlbum(string name_,string color_,int x_,int y_)
        {
            name = name_;
            color = color_;
            x= x_;
            y = y_;

            next = 0;
            before = 0;
            up  = 0;
            down = 0;
        }
        

        
        string getName() {return name;}
        string getColor(){ return color;}
        int getX() {return x;}
        int getY(){return y;}
        

        NodoAlbum *getNext(){ return next;}
        NodoAlbum *getBefore() {return before;}
        NodoAlbum *getUp(){ return up;}
        NodoAlbum *getDown() {return down;}
        void setNext(NodoAlbum *n) { next = n;}
        void setBefore(NodoAlbum *n){ before = n;}
        void setUp(NodoAlbum *n) { up = n;}
        void setDown(NodoAlbum *n){ down = n;}
        
        
     private:
        string name;
        string color;
        int x;
        int y;

        NodoAlbum *next;
        NodoAlbum *before;
        NodoAlbum *up;
        NodoAlbum *down;
        
    };
    #endif