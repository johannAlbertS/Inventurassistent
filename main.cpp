#include <iostream>
#include <ostream>
#include <string>
#include <list>
#include "Klasse.h"
#include "Funktionen.h"
#include <string.h>
using namespace std;

void help();
void interactivemode(Listenfunktionen&);

int main(int argc, char *argv[])
{
    Listenfunktionen f;
    f.lesen();
    if(strcmp(argv[1], "einbuchen") == 0)
    {
        f.anhaengen();
        f.schreiben();
    }
    else if(strcmp(argv[1], "ausgeben") == 0)
    {
        f.ausgeben();
    }
    else if(strcmp(argv[1], "loeschen") == 0)
    {
        f.ausgeben();
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

inline void help()
{
    cout << "This is Inventurassistent by Albert Scherezer" << endl
         << "With this programm you can log what's in your fridge" << endl
         << endl
         << "Usuage:" << endl
         << "./Inventurassistent [OPTION]" << endl
         << endl 
         << "You can run this programm in interactive mode or as a cli" << endl
         << endl
         << "For interactive mode use this option:" << endl
         << "i: \t interactive mode" << endl
         << endl
         << "for the cli there these options:" << endl
         << "einbuchen: \t put something in the fridge" << endl
         << "ausbuchen: \t take something out of the fridge" << endl
         << "ausgeben: \t see what's in your fridge" << endl
         << "help: \t\t see this help" << endl;
}

void interactivemode(Listenfunktionen& f)
{
    bool Abbruch = false;
        do
        {
            cout << "Was willst du machen? Einbuchen(n), Ausbuchen(r), ausgeben(a), oder beenden(x)\n";
            char Wahl;
            cin >> Wahl;
            switch (Wahl)
            {
                case 'n':
                    f.anhaengen();
                    break;
                case 'r':
                    f.ausgeben();
                    f.loeschen();
                    break;
                case 'a':
                    f.ausgeben();
                    break;
                case 'x':
                    f.schreiben();
                    Abbruch = true;
                    break;
                default:
                    cout << "n, r, a oder x\n";
            }
        } while (Abbruch == false);
}
