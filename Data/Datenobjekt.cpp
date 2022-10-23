#include <iostream>
#include <fstream>
#include <string>
#include "Datenobjekt.h"
using namespace std;

int Inventurdaten::Anzahl = 0;

//Konstruktor
Inventurdaten::Inventurdaten() : Art(""), Menge(0), Einheit("") {}

void Inventurdaten::DatenRaus()
{
  cout << Menge << " " << Einheit << " " << Art << endl;
}

//Ausgabe je nach ob 1 oder mehr/weniger 
void Inventurdaten::AnzahlRaus()
{
	if (Anzahl != 1)
	{
		cout << "Es werden aktuell " << Anzahl << " Objekte gelagert\n";
	}
	else
	{
		cout << "Es wird aktuell ein Objekt gelagert\n";
	}
}

//Streams zum formartierten eingeben
istream& operator>>(istream& is, Inventurdaten& i)
{
  cout << "Was ist es? "; is >> i.Art;
  cout << "Wie viel davon? ";
  is >> i.Menge >> i.Einheit;
  //Erst wenn es mit Daten befüllt wird soll es in die Anzahl aufgenommen werden
  i.Anzahl += 1;
  return is;
}

//Formartierte Ausgabe über Streams
ostream& operator<<(ostream& os, Inventurdaten& i)
{
  cout << i.Menge << " " << i.Einheit << " " << i.Art << endl;
  return os;
}

//Inkrementieren und Dekrementieren
void Inventurdaten::KleinerAnzahl()
{
  Anzahl -= 1;
}

void Inventurdaten::GroesserAnzahl()
{
	Anzahl += 1;
}

//Schreiben von Daten in File über Streams
ofstream& operator<<(ofstream& of, Inventurdaten& i)
{
  of << i.Art << " " << i.Menge << " " << i.Einheit << endl;
  return of;
}

//Lesen aus File über Streams
ifstream& operator>>(ifstream& is, Inventurdaten& i)
{
  is >> i.Art >> i.Menge >> i.Einheit;
  i.Anzahl += 1;
  return is;
}

//Destruktor
Inventurdaten::~Inventurdaten()
{
	Anzahl--;
}