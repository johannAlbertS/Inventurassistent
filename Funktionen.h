#include <iostream>
#include <list>
#include "Klasse.h"
using namespace std;

#ifndef __FUNKTIONEN__
#define __FUNKTIONEN__
class Listenfunktionen
{
  private:
    //Liste an Objekten mit den Daten
    list<Inventurdaten> l;
  public:
    //Element an Liste anhängen 
    void anhaengen();
    //Ausgeben und Loeschen
    void ausgeben();
    void loeschen();
    //Aus File lesen und schreiben
    void schreiben();
    void lesen();
};
#endif
