#include <bits/types/time_t.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
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
    //Dies speichert die Anzahl aller Klassen
    static int Anzahl;
    //Konstruktor
    Inventurdaten();
    //Daten ausgeben
    void DatenRaus();
    double MengeRaus();
    //Die Anzahl ausgeben
    void AnzahlRaus();
    //Anzahl imkrementieren/dekrementieren
    void KleinerAnzahl();
    void GroesserAnzahl();
    //Formartierte Aus/Eingabe über Streams
    friend ofstream& operator<<(ofstream&, Inventurdaten&);
    friend ifstream& operator>>(ifstream&, Inventurdaten&);
    //Operatoren
    bool operator==(Inventurdaten&);
    Inventurdaten& operator+=(Inventurdaten&);
    Inventurdaten& operator-=(Inventurdaten&);
    double operator-(Inventurdaten&);
    //Eingabe des Datums
    void Datumseingabe();
    //Ein/Ausgabe in Files über Streams
    friend ostream& operator<<(ostream&, Inventurdaten&);
    friend istream& operator>>(istream&, Inventurdaten&);
    //Destruktor
    ~Inventurdaten();
};
#endif
