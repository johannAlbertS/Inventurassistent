#include <iostream>
#include <list>
#include "Datenobjekt.h"
#include <sqlite3.h>
#include <string>
using namespace std;

#ifndef __FUNKTIONEN__
#define __FUNKTIONEN__
class Listenfunktionen
{
  private:
    //Liste an Objekten mit den Daten
    list<Inventurdaten> l;
    //In welcher Datei die Daten gespeichert werden sollen
    string Liste;
    //string Databasefile;
    string Verb;
    bool zeigeDatum;
    sqlite3* db;
  public:
    //Konstruktor
    Listenfunktionen();
    Listenfunktionen(sqlite3*, const string&, const string&, bool);
    //Element an Liste anhängen 
    void anhaengen();
    void anhaengenmitgleich(Inventurdaten&);
    //Für die Einkaufsliste
    void Listenvergleich(Listenfunktionen&, Listenfunktionen&);
    //Ausgeben und Loeschen
    void ausgeben();
    void loeschen();
    bool loeschen(Inventurdaten&);
    //Aus File lesen und schreiben
    void schreiben();
    void lesen();
};
#endif
