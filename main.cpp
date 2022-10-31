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
    Listenfunktionen f("Daten.txt");
    f.lesen();
    //Die jeweiligen CLI-Kommandos
    if(strcmp(argv[1], "einbuchen") == 0)
    {
        f.anhaengen();
        f.schreiben();
    }
    else if(strcmp(argv[1], "ausgeben") == 0)
    {
        f.ausgeben();
    }
    else if(strcmp(argv[1], "ausbuchen") == 0)
    {
        //f.ausgeben();
        f.loeschen();
        f.schreiben();
    }
    else if(strcmp(argv[1], "i") == 0)
    {
        interactivemode(f);
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
