#ifndef NODOALBUM_H_INCLUDE
#define NODOALBUM_H_INCLUDE
#include <iostream>
#include <string>
using namespace std;
#include "ListaEnlazada.h"
#include "NodoSong.h"

class NodoAlbum{
    public:
        NodoAlbum(string name_,string month_,string year_)
        {
            name = name_;
            month = month_;
            year = year_;
            listta= 0;
            rating = 0;

            next = 0;
            before = 0;
            up  = 0;
            down = 0;
            ade  = 0;
            atr = 0; 
        }
        NodoAlbum(string name_,string month_,string year_,Lista<NodoSong*> * l,double r)
        {
            name = name_;
            month = month_;
            year = year_;
            listta= l;
            rating = r;

            next = 0;
            before = 0;
            up  = 0;
            down = 0;
            ade  = 0;
            atr = 0; 
        }
        

        
        string getName() {return name;}
        string getMonth(){ return month;}
        string getYear() {return year;}
        double getRating(){return rating;}
        Lista<NodoSong*> *getLista(){return listta;}
        

        NodoAlbum *getNext(){ return next;}
        NodoAlbum *getBefore() {return before;}
        NodoAlbum *getUp(){ return up;}
        NodoAlbum *getDown() {return down;}
        NodoAlbum *getAde(){ return ade;}
        NodoAlbum *getAtr() {return atr;}
        void setNext(NodoAlbum *n) { next = n;}
        void setBefore(NodoAlbum *n){ before = n;}
        void setUp(NodoAlbum *n) { up = n;}
        void setDown(NodoAlbum *n){ down = n;}
        void setAde(NodoAlbum *n) { ade = n;}
        void setAtr(NodoAlbum *n){ atr = n;}
        
        
     private:
        Lista<NodoSong*> *listta;
        string name;
        string month;
        string year;
        double rating;

        NodoAlbum *next;
        NodoAlbum *before;
        NodoAlbum *up;
        NodoAlbum *down;
        NodoAlbum *ade;
        NodoAlbum *atr;
        
    };
    #endif