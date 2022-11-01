#include <iostream>
#include <ostream>
#include <string>
#include <list>
#include "Datahandling/Datenobjekt.h"
#include "Datahandling/Listenobjekt.h"
#include "Funktionen.h"
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
    //Wenn kein Argument übergeben wurde kann nichts gemacht werden
    if(argc <= 1)
    {
        cout << "No Argument given, aborting\n";
        return 0;
    }
    Listenfunktionen Data("Daten.txt", "gelagert", true);
    Listenfunktionen Soll("Soll.txt", "als benötigt gespeichert", false);
    Listenfunktionen Muss("Muss.txt", "gebraucht", false);
    Data.lesen();
    Soll.lesen();
    Muss.lesen();
    //Die jeweiligen CLI-Kommandos
    if(strcmp(argv[1], "einbuchen") == 0)
    {
        if(strcmp(argv[2], "daten") == 0)
        {
            Data.anhaengen();
            Data.schreiben();
            Soll.Listenvergleich(Data, Muss);
            Muss.schreiben();
        }
        else if(strcmp(argv[2], "sollbestand") == 0)
        {
            Soll.anhaengen();
            Soll.schreiben();
            Soll.Listenvergleich(Data, Muss);
            Muss.schreiben();
        }
        else cout << "Falsches Argument\n";
    }
    else if(strcmp(argv[1], "ausgeben") == 0)
    {
        if(strcmp(argv[2], "daten") == 0) Data.ausgeben();
        else if(strcmp(argv[2], "nachkaufen") == 0) Muss.ausgeben();
        else if(strcmp(argv[2], "sollbestand") == 0) Soll.ausgeben();
        else cout << "Falsches Argument\n";
    }
    else if(strcmp(argv[1], "ausbuchen") == 0)
    {
        if(strcmp(argv[2], "daten") == 0)
        {
            Data.loeschen();
            Data.schreiben();
            Soll.Listenvergleich(Data, Muss);
            Muss.schreiben();
        }
        else if(strcmp(argv[2], "sollbestand") == 0)
        {
            Soll.loeschen();
            Soll.schreiben();
            Soll.Listenvergleich(Data, Muss);
            Muss.schreiben();
        }
        else cout << "Falsches Argument\n";
    }
    else if(strcmp(argv[1], "i") == 0)
    {
        interactivemode(Data, Soll, Muss);
    }
    else if(strcmp(argv[1], "help") == 0)
    {
        help();
    }
    else
    {
        cout << "Es wurde kein passender Befehl eingegeben\n";
    }
    return 0;
}
