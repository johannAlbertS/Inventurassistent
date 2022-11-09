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
  Verb = "";
  zeigeDatum = true;
}

Listenfunktionen::Listenfunktionen(const string& dateiname, const string& verb, bool zD)
{
  Dateiname = dateiname;
  Verb = verb;
  zeigeDatum = zD;
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
  }
  //l.push_back(tempObj);
  //tempObj.GroesserAnzahl();
}

void Listenfunktionen::anhaengenmitgleich(Inventurdaten& i)
{
  bool gefunden = false;
  for(auto it = begin(l); it != end(l); ++it)
  {
    if(it->operator==(i) == true)
    {
      it->operator=(i);
      gefunden = true;
    }
  }
  if(gefunden != true)
  {
    l.push_back(i);
  }
}

void Listenfunktionen::Listenvergleich(Listenfunktionen& mit, Listenfunktionen& zu)
{
  for(auto it = begin(l); it != end(l); ++it)
  {
    bool gefunden = false;
    for(auto it2 = begin(mit.l); it2 != end(mit.l); ++it2)
    {
      if(*it2 == *it && (it->operator-(*it2)) > 0)
      {
        Inventurdaten i = it->minus(*it2);
        zu.anhaengenmitgleich(i);
        gefunden = true;
        break;
      }
      else if(*it == *it && it->operator-(*it2) <= 0)
      {
        //Nichts tun
        zu.loeschen(*it);
        gefunden = true;
        break;
      }
    }
    if(gefunden == false)
    {
      zu.anhaengenmitgleich(*it);
    }
  }
}

//Falls leer entsprechende Meldungs, sonst iterieren und über DatenRaus() ausgeben, davor AnzahlRaus()
void Listenfunktionen::ausgeben()
{
  if (l.empty())
  {
      cout << "Es werden aktuell keine Objekte " << Verb << endl;
  }
  else
  {
      list<Inventurdaten>::iterator it1 = begin(l);
      if(l.size() == 1) cout << "Es wird aktuell ein Objekt " << Verb << endl;
      else cout << "Es werden aktuelle " << l.size() << " Objekte " << Verb << endl;
      int Zaehler = 1;
      if(zeigeDatum == true)
      {
        for (auto it2 = begin(l); it2 != end(l); ++it2)
        {
          cout << Zaehler << ". " << endl;
          it2->DatenRaus(true);
          Zaehler++;
        }
      }
      else
      {
        for (auto it2 = begin(l); it2 != end(l); ++it2)
        {
          cout << Zaehler << ". " << endl;
          it2->DatenRaus(false);
          Zaehler++;
        }
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

bool Listenfunktionen::loeschen(Inventurdaten& i)
{
  bool gefunden = false;
  for(auto it = begin(l); it != end(l); ++it)
  {
    if(it->operator==(i) == true)
    {
      l.erase(it);
      gefunden = true;
      break;
    }
  }
  if(gefunden == true)
  {
    return true;
  }
  else return false;
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
