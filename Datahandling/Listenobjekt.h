#include <iostream>
#include <list>
#include "Datenobjekt.h"
using namespace std;

#ifndef __FUNKTIONEN__
#define __FUNKTIONEN__
class Listenfunktionen
{
  private:
    //Liste an Objekten mit den Daten
    list<Inventurdaten> l;
    //In welcher Datei die Daten gespeichert werden sollen
    string Dateiname;
  public:
    //Konstruktor
    Listenfunktionen();
    Listenfunktionen(const string&);
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
