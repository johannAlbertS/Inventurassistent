#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#ifndef __INVENTURDATEN__
#define __INVENTURDATEN__

class Inventurdaten
{
private:
    //Art hält fest was es ist also z.B. Ente, Rindergulasch, oder Wuerstchen 
    string Art;
    //Selbsterklärend
    int Menge;
    string Einheit;
public:
    //Dies speichert die Anzahl aller Klassen
    static int Anzahl;
    //Konstruktor
    Inventurdaten();
    //Daten ausgeben
    void DatenRaus();
    //Die Anzahl ausgeben
    void AnzahlRaus();
    //Anzahl imkrementieren/dekrementieren
    void KleinerAnzahl();
    void GroesserAnzahl();
    //Formartierte Aus/Eingabe über Streams
    friend ofstream& operator<<(ofstream&, Inventurdaten&);
    friend ifstream& operator>>(ifstream&, Inventurdaten&);
    //Ein/Ausgabe in Files über Streams
    friend ostream& operator<<(ostream&, Inventurdaten&);
    friend istream& operator>>(istream&, Inventurdaten&);
    //Destruktor
    ~Inventurdaten();
};
#endif
