#include <iostream>
#include <iterator>
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include "Listenobjekt.h"

using namespace std;

Listenfunktionen::Listenfunktionen()
{
  Dateiname = "";
}

Listenfunktionen::Listenfunktionen(const string& dateiname)
{
  Dateiname = dateiname;
}

void Listenfunktionen::anhaengen()
{
  Inventurdaten tempObj;
  cin >> tempObj;
  tempObj.Datumseingabe();
  bool gefunden = false;
  for(auto it = begin(l); it != end(l); ++it)
  {
    if(it->operator==(tempObj) == true)
    {
      it->operator+=(tempObj);
      gefunden = true;
    }
  }
  if(gefunden != true)
  {
    l.push_back(tempObj);
    tempObj.GroesserAnzahl();
  }
  //l.push_back(tempObj);
  //tempObj.GroesserAnzahl();
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
    cout << "Nichts drinnen\n";
  }
  Inventurdaten tempObj;
  cout << "Was soll raus\n";
  cin >> tempObj;
  bool gefunden = false;
  for(list<Inventurdaten>::iterator it = begin(l); it != end(l); ++it)
  {
    if(it->operator==(tempObj) == true && it->operator-(tempObj) > 0)
    {
      it->operator-=(tempObj);
      gefunden = true;
      break;
    }
    else if(it->operator==(tempObj) == true && it->operator-(tempObj) <= 0)
    {
      l.erase(it);
      gefunden = true;
      break;
    }
  }
  if(gefunden == false)
  {
    cout << "Dieses Objekt ist nicht in der Tiefkühltruhe\n";
  }
}

//Schreiben wenn etwas drin durch iterieren und nutzen des Streams
void Listenfunktionen::schreiben()
{
  ofstream datei(Dateiname.c_str()); 
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
  ifstream lesen(Dateiname.c_str());
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
