#include <iostream>
#include <string>
#include <ctime>
#include <sqlite3.h>
using namespace std;

#ifndef __INVENTURDATEN__
#define __INVENTURDATEN__

class Inventurdaten
{
private:
    //Art hält fest was es ist also z.B. Ente, Rindergulasch, oder Wuerstchen 
    string Art;
    //Selbsterklärend
    double Menge;
    string Einheit;
    //Das Verfallsdatum
    time_t Verfallsdatum;
public:
    //Konstruktoren
    Inventurdaten();
    Inventurdaten(string&, double, string&);
    Inventurdaten(string&, double, string&, time_t);
    //Daten ausgeben
    void DatenRaus(bool);
    double MengeRaus();
    //Formartierte Aus/Eingabe über Streams
    friend ofstream& operator<<(ofstream&, Inventurdaten&);
    friend ifstream& operator>>(ifstream&, Inventurdaten&);
    //Operatoren
    bool operator==(Inventurdaten&);
    Inventurdaten& operator=(Inventurdaten&);
    Inventurdaten& operator+=(Inventurdaten&);
    Inventurdaten& operator-=(Inventurdaten&);
    double operator-(Inventurdaten&);
    Inventurdaten minus(Inventurdaten&);
    //Eingabe des Datums
    void Datumseingabe();
    //Ein/Ausgabe in Files über Streams
    //friend ostream& operator<<(ostream&, Inventurdaten&);
    //friend istream& operator>>(istream&, Inventurdaten&);
    void eingeben();
    //Funktionen zum Schreiben in der Datenbank
    void insert(sqlite3*, int);
    void remove(sqlite3*, int);
    void update(sqlite3*, int);
    //Destruktor
    ~Inventurdaten();
};
#endif
