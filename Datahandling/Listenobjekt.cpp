#include <iostream>
#include <list>
#include <sqlite3.h>
#include <string>
#include "Listenobjekt.h"
#include <cstring>
#include <sstream>
#include <thread>

using namespace std;

Listenfunktionen::Listenfunktionen()
{
  //Databasefile = "";
  Liste = "";
  Verb = "";
  zeigeDatum = true;
}

Listenfunktionen::Listenfunktionen(sqlite3* database, const string& verb, const string& liste, bool zD)
{
  thread t([&] () {sqlite3_stmt* idstmt;
                      string idstatement = "select rowid from liste where titel = '" + liste + "'";
                      const char * idstatementStr = idstatement.c_str();
                      sqlite3_prepare_v2(database, idstatementStr, static_cast<int>(strlen(idstatementStr)), &idstmt, NULL);
                      if(sqlite3_step(idstmt) == SQLITE_ROW)
                      {
                        listid = sqlite3_column_int64(idstmt, 0);
                      }
                      else cout << "Es ist etwas schiefgelaufen\n";}
          );
  t.join();
  db = database;
  Liste = liste;
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
      it -> update(db, listid);
      gefunden = true;
    }
  }
  if(gefunden != true)
  {
    l.push_back(tempObj);
    tempObj.insert(db, listid);
  }
}

void Listenfunktionen::anhaengenmitgleich(Inventurdaten& i)
{
  bool gefunden = false;
  for(auto it = begin(l); it != end(l); ++it)
  {
    if(it->operator==(i) == true)
    {
      it->operator=(i);
      it -> update(db, listid);
      gefunden = true;
    }
  }
  if(gefunden != true)
  {
    l.push_back(i);
    i.insert(db, listid);
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
      else cout << "Es werden aktuell " << l.size() << " Objekte " << Verb << endl;
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
      it -> update(db, listid);
      gefunden = true;
      break;
    }
    else if(it->operator==(tempObj) == true && it->operator-(tempObj) <= 0)
    {
      it -> remove(db, listid);
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

void Listenfunktionen::loeschen(Inventurdaten& i)
{
  for(auto it = begin(l); it != end(l); ++it)
  {
    if(it->operator==(i) == true)
    {
      it -> remove(db, listid);
      l.erase(it);
      break;
    }
  }
}

//Statement erstellen und ausführen sollange es noch was neues gibt
void Listenfunktionen::lesen()
{
  sqlite3_stmt* leseBefehle;
  string datastatement = "select art, menge, einheit, verfallsdatum from daten where listid = " + to_string(listid);
  const char * datastatementStr = datastatement.c_str();
  sqlite3_prepare_v2(db, datastatementStr, static_cast<int>(strlen(datastatementStr)), &leseBefehle, NULL);
  while(sqlite3_step(leseBefehle) == SQLITE_ROW)
  {
    const unsigned char * art = sqlite3_column_text(leseBefehle, 0);
    const unsigned char * einheit = sqlite3_column_text(leseBefehle, 2);
    double menge = sqlite3_column_double(leseBefehle, 1);
    time_t verfallsdatum = sqlite3_column_int(leseBefehle, 3);
    ostringstream artstream, einheitstream; string arts, einheits;
    artstream << art; arts = artstream.str();
    einheitstream << einheit; einheits = einheitstream.str();
    Inventurdaten puffer(arts, menge, einheits, verfallsdatum);
    l.push_back(puffer);
  }
}
