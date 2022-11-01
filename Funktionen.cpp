#include <iostream>
#include "Funktionen.h"
using namespace std;

void help()
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
         << "einbuchen: \t put something in a list" << endl
         << "\t \t with 'daten' into the fridge, with 'sollbestand' into the list what you want to have" << endl
         << "ausbuchen: \t take something out of a list" << endl
         << "\t \t with 'daten' out of the fridge, with 'sollbestand' out of the list what you want to have" << endl
         << "ausgeben: \t see what's in your fridge" << endl
         << "\t \t with 'daten' what's in the fridge, with 'nachkaufen' what you need to buy and with 'sollbestand' what you want to have"  << endl
         << "help: \t\t see this help" << endl;
}

void interactivemode(Listenfunktionen& data, Listenfunktionen& soll, Listenfunktionen& muss)
{
    bool Abbruch = false;
    cout << "Was möchtest du machen?\n";
    cout << "Du kannst dir den Inhalt der Tiefkühltruhe(a), die Sollbestände(s) oder die Einkaufsliste(k) ausgeben lassen\n";
    cout << "oder ein-und ausbuchen mit (n bzw. r). Oder du beendest mit x\n";
    do
    {
        cout << "Was willst du machen?\n";
        string Wahlstr;
        char Wahl;
        cin >> Wahlstr;
        Wahl = Wahlstr[0];
        string Wahlstr2;
        char Wahl2;
        switch(Wahl)
        {
            case 'x':
                data.schreiben();
                soll.schreiben();
                muss.schreiben();
                Abbruch = true;
                break;
            case 'a': data.ausgeben();
                break;
            case 's': soll.ausgeben();
                break;
            case 'k': muss.ausgeben();
                break;
            case 'n':
                cout << "In die Tiefkühltruhe(t) oder in den Sollbestand(s)?\n";
                cin >> Wahlstr2;
                Wahl2 = Wahlstr2[0];
                switch(Wahl2)
                {
                    case 't':
                       data.anhaengen();
                       break;
                    case 's':
                       soll.anhaengen();
                       break;
                    default: cout << "Nur s oder t erlaubt\n";
                }
                soll.Listenvergleich(data, muss);
                break;
            case 'r':
                cout << "In die Tiefkühltruhe(t) oder in den Sollbestand(s)?\n";
                cin >> Wahlstr2;
                Wahl2 = Wahlstr2[0];
                switch(Wahl2)
                {
                    case 't':
                       data.loeschen();
                       break;
                    case 's':
                       soll.loeschen();
                       break;
                    default: cout << "Nur s oder t erlaubt\n";
                }
                soll.Listenvergleich(data, muss);
                break;
            default: 
               cout << "x, a, s, k oder b sonst nichts\n";
        }
        /*cout << "Was willst du machen? Einbuchen(n), Ausbuchen(r), ausgeben(a), oder beenden(x)\n";
        char Wahl;
        cin >> Wahl;
        switch (Wahl)
        {
            case 'n':
                f.anhaengen();
                break;
            case 'r':
                //f.ausgeben();
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
        }*/
    } while (Abbruch == false);
}
