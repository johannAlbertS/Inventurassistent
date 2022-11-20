#include <iostream>
#include <string>
#include "Datahandling/Datenobjekt.h"
#include "Datahandling/Listenobjekt.h"
#include "Funktionen.h"
#include <string.h>
#include <sqlite3.h>
#include <thread>
using namespace std;

int main(int argc, char *argv[])
{
    //Wenn kein Argument übergeben wurde kann nichts gemacht werden
    if(argc <= 1)
    {
        cout << "No Argument given, aborting\n";
        return 0;
    }
    sqlite3* database;
    sqlite3_open("Daten.db", &database);
    thread t1(createDBSchemeifnotexists, database);
    t1.join();
    Listenfunktionen Data(database, "gelagert", "ist", true);
    Listenfunktionen Soll(database, "als benötigt gespeichert", "soll", false);
    Listenfunktionen Muss(database, "gebraucht", "muss", false);
    Data.lesen();
    Soll.lesen();
    Muss.lesen();
    //Die jeweiligen CLI-Kommandos
    if(strcmp(argv[1], "einbuchen") == 0)
    {
        if(argc >= 3)
        {
            if(strcmp(argv[2], "daten") == 0)
            {
                Data.anhaengen();
                Soll.Listenvergleich(Data, Muss);
            }
            else if(strcmp(argv[2], "sollbestand") == 0)
            {
                Soll.anhaengen();
                Soll.Listenvergleich(Data, Muss);
            }
            else cout << "Falsches Argument\n";
        }
        else cout << "Du mussst noch die Liste spezifizieren!\n";
    }
    else if(strcmp(argv[1], "ausgeben") == 0)
    {
        if(argc >= 3)
        {
            if(strcmp(argv[2], "daten") == 0) Data.ausgeben();
            else if(strcmp(argv[2], "nachkaufen") == 0) Muss.ausgeben();
            else if(strcmp(argv[2], "sollbestand") == 0) Soll.ausgeben();
            else cout << "Falsches Argument\n";
        }
        else cout << "Du musst noch die Liste spezifizieren!\n";
    }
    else if(strcmp(argv[1], "ausbuchen") == 0)
    {
        if(argc >= 3)
        {
            if(strcmp(argv[2], "daten") == 0)
            {
                Data.loeschen();
                Soll.Listenvergleich(Data, Muss);
            }
            else if(strcmp(argv[2], "sollbestand") == 0)
            {
                Soll.loeschen();
                Soll.Listenvergleich(Data, Muss);
            }
            else cout << "Falsches Argument\n";
        }
        else cout << "Du musst noch die Liste spezifizieren!\n";
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
