#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "Datenobjekt.h"
using namespace std;

//Konstruktoren
Inventurdaten::Inventurdaten() : Art(""), Menge(0), Einheit(""), Verfallsdatum(0) {}

Inventurdaten::Inventurdaten(string& a, double m, string& e) : Art(a), Menge(m), Einheit(e), Verfallsdatum(0) {}

Inventurdaten::Inventurdaten(string& a, double m, string& e, time_t v) : Art(a), Menge(m), Einheit(e), Verfallsdatum(v) {}

void Inventurdaten::DatenRaus(bool mitDatum)
{
  cout << Menge << " " << Einheit << " " << Art << endl;
  time_t now = time(0);
  if(mitDatum == true)
  {
    if(Verfallsdatum == 0)
    {
      cout << "Kein Verfallsdatum angegeben\n";
    }
    else if(Verfallsdatum < now && Verfallsdatum != 0)
    {
      cout << "Bereits abgelaufen\n";
    }
    else
    {
      char datum[26];
      ctime_r(&Verfallsdatum, datum);
      cout << "Verfällt am: " << datum << '\n';
    } 
  }
}

double Inventurdaten::MengeRaus()
{
  return Menge;
}

//Streams zum formartierten eingeben
istream& operator>>(istream& is, Inventurdaten& i)
{
  cout << "Was ist es? "; is >> i.Art; //getline(is, i.Art);
  cout << "Wie viel davon? ";
  is >> i.Menge >> i.Einheit;
  return is;
}

//Datumseingabe
void Inventurdaten::Datumseingabe()
{
  tm *date = new tm;
  int year, month, day;
  bool datacorrect = false;
  bool Datumda=true;
  char Datumdac;
  cout << "Hat das Produkt ein Verfallsdatum(j/n)? "; cin >> Datumdac;
  if(Datumdac == 'n')
  {
    Datumda = false;
    Verfallsdatum = 0;
  }
  else
  {
    cout << "Das Produkt verfällt am?\n";
    while(datacorrect == false)
    {
      cout << "Tag: "; cin >> day;
      cout << "Monat: "; cin >> month;
      cout << "Jahr: "; cin >> year;
      if((month == 2 && day <= 30) || (month == 4 && day <= 30) ||
        (month == 6 && day <= 30) || (month == 9 && day <= 30) || (month == 11 && day <= 30))
      {
        datacorrect = true; 
      }
      else if ((month == 1 && day <= 31) || (month == 3 && day <= 31) || (month == 5 && day <= 31) || 
        (month == 7 && day <= 31)  || (month == 8 && day <= 31)  || (month == 10 && day <= 31)  || (month == 12 && day <= 31))
      {
        datacorrect = true;
      }
      else
      {
        cout << "Die Zahlen passen nicht ganz, bitte noch mal eintippen\n";
      }
    }
    date -> tm_year = year - 1900;
    date -> tm_mon = month - 1;
    date -> tm_mday = day;
    date -> tm_sec = 0; date -> tm_min = 0; date -> tm_hour = 0; date -> tm_wday = 0; date -> tm_yday = 0; date -> tm_isdst = 0;
    Verfallsdatum = mktime(date);
    delete date;
  }
}

//Formartierte Ausgabe über Streams
ostream& operator<<(ostream& os, Inventurdaten& i)
{
  cout << i.Menge << " " << i.Einheit << " " << i.Art << endl;
  return os;
}

//Operatoren
bool Inventurdaten::operator==(Inventurdaten &i)
{
  if(this->Art == i.Art && this->Einheit == i.Einheit) return true;
  else return false;
}
Inventurdaten& Inventurdaten::operator=(Inventurdaten& i)
{
  this->Art = i.Art; this->Menge = i.Menge; this->Einheit = i.Einheit; this->Verfallsdatum = 0;
  return *this;
}

Inventurdaten& Inventurdaten::operator+=(Inventurdaten &i)
{
  this->Menge+=i.Menge;
  if((this->Verfallsdatum > i.Verfallsdatum) || (this->Verfallsdatum == 0 && i.Verfallsdatum > 0))
  {
    this->Verfallsdatum=i.Verfallsdatum;
  }
  return *this;
}

Inventurdaten& Inventurdaten::operator-=(Inventurdaten& i)
{
  this->Menge-=i.Menge;
  return *this;
}

double Inventurdaten::operator-(Inventurdaten& i)
{
  return this->Menge - i.Menge;
}

Inventurdaten Inventurdaten::minus(Inventurdaten& i)
{
  Inventurdaten temp(i.Art, this->Menge - i.Menge, i.Einheit);
  return temp;
}

//Schreiben von Daten in File über Streams
ofstream& operator<<(ofstream& of, Inventurdaten& i)
{
  of << i.Art << "\n" << i.Menge << " " << i.Einheit << " " << i.Verfallsdatum << endl;
  return of;
}

//Lesen aus File über Streams
ifstream& operator>>(ifstream& is, Inventurdaten& i)
{
  is >> i.Art >> i.Menge >> i.Einheit >> i.Verfallsdatum;
  return is;
}

//Funktionen zum Schreiben in der Datenbank
//Prinzip Statement erzeugen, mit den eigenen Daten anreichern, ausführen und schauen ob es erfolgreich war
void Inventurdaten::insert(sqlite3* db, int listid)
{
  sqlite3_stmt* stmt;
  string statement = "insert into daten values ('" + Art + "', " + to_string(Menge) + ", '" + Einheit + "', " +
                      to_string(Verfallsdatum) + ", " + to_string(listid) + ")";
  const char * statementStr = statement.c_str();
  sqlite3_prepare_v2(db, statementStr, static_cast<int>(strlen(statementStr)), &stmt, NULL);
  if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Da ist etwas schiefgelaufen\n";
}

void Inventurdaten::remove(sqlite3* db, int listid)
{
  sqlite3_stmt* stmt;
  string statement = "delete from daten where art = '" + Art + "' and einheit = '" + Einheit + "' and listid = " + 
                      to_string(listid);
  const char * statementStr = statement.c_str();
  sqlite3_prepare_v2(db, statementStr, static_cast<int>(strlen(statementStr)), &stmt, NULL);
  if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Da ist etwas schiefgelaufen\n";
}

void Inventurdaten::update(sqlite3* db, int listid)
{
  sqlite3_stmt* stmt;
  string statement = "update daten set menge = " + to_string(Menge) + ", verfallsdatum = " + to_string(Verfallsdatum) + 
                     " where art = '" + Art + "' and einheit = '" + Einheit + "' and listid = " + to_string(listid);
  const char * statementStr = statement.c_str();
  sqlite3_prepare_v2(db, statementStr, static_cast<int>(strlen(statementStr)), &stmt, NULL);
  if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Da ist etwas schiefgelaufen\n";
}

//Destruktor
Inventurdaten::~Inventurdaten()
{}
