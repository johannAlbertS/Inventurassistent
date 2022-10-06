#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include "Funktionen.h"
#include "Klasse.h"

using namespace std;

void Listenfunktionen::anhaengen()
{
  Inventurdaten tempObj;
  cin >> tempObj;
  l.push_back(tempObj);
  tempObj.GroesserAnzahl();
}

//Falls leer entsprechende Meldungs, sonst iterieren und über DatenRaus() ausgeben, davor AnzahlRaus()
void Listenfunktionen::ausgeben()
{
  if (l.empty())
  {
      cout << "Es werden aktuell keine Objekte gelagert\n";
  }
  else
  {
      list<Inventurdaten>::iterator it1 = begin(l);
      it1->AnzahlRaus();
      int Zaehler = 1;
      for (auto it2 = begin(l); it2 != end(l); ++it2)
      {
          cout << Zaehler << ". " << endl;
          it2->DatenRaus();
          Zaehler++;
      }
  }
}

//Da in main.cpp ausgeben() vor loeschen() aufgerufen wird kommt keine Meldung wenn leer
//Ansonsten Iterieren und loeschen
void Listenfunktionen::loeschen()
{
  if (l.empty())
  {
     //Die Ausgabe dass es nichts gibt wird von ausgeben() uebernommen
  }
  else
  {
      cout << "Das wievielte Element soll raus? ";
      int raus; cin >> raus;
      list<Inventurdaten>::iterator it = begin(l);
      for (int i = 0; i < raus - 1; i++) it++;
      l.erase(it);
  }
}

//Schreiben wenn etwas drin durch iterieren und nutzen des Streams
void Listenfunktionen::schreiben()
{
  ofstream datei("Daten.txt"); 
  if (l.empty())
  {
      //Nichts tun...
  }
  else
  {
      for (auto it = begin(l); it != end(l); ++it)
      {
          datei << *it;
      }
  }
}

//Über Stream lesen und push_backen()
void Listenfunktionen::lesen()
{
  ifstream lesen("Daten.txt");
  Inventurdaten puffer;
  while (lesen >> puffer)
  {
      l.push_back(puffer);
  }
  if (l.empty() == true)
  {
     //Nichts tun
  }
}
