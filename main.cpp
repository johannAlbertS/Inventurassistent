#include <iostream>
#include <string>
#include <list>
#include "Klasse.h"
#include "Funktionen.h"
using namespace std;

int main()
{
    Listenfunktionen f;
    f.lesen();
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
    return 0;
}
