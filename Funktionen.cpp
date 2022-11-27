#include <iostream>
#include <thread>
#include <cstring>
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
        if(Wahlstr.size() > 1)
        {
            cout << "EINEN Buchstaben\n";
            continue;
        } 
        else Wahl = Wahlstr[0]; 
        string Wahlstr2;
        char Wahl2;
        switch(Wahl)
        {
            case 'x':
                Abbruch = true;
                break;
            case 'a': data.ausgeben();
                break;
            case 's': soll.ausgeben();
                break;
            case 'k': muss.ausgeben();
                break;
            case 'n':
                do
                {
                    cout << "In die Tiefkühltruhe(t) oder in den Sollbestand(s)?\n";
                    cin >> Wahlstr2;
                } while(Wahlstr2.size() > 1);
                Wahl2 = Wahlstr2[0];
                switch(Wahl2)
                {
                    case 't':
                       data.anhaengen(true);
                       break;
                    case 's':
                       soll.anhaengen(true);
                       break;
                    default: cout << "Nur s oder t erlaubt\n";
                }
                soll.Listenvergleich(data, muss);
                break;
            case 'r':
                do
                {
                    cout << "Aus der Tiefkühltruhe(t) oder aus dem Sollbestand(s)?\n";
                    cin >> Wahlstr2;
                } while(Wahlstr2.size() > 1);
                Wahl2 = Wahlstr2[0];
                switch(Wahl2)
                {
                    case 't':
                       data.loeschen(true);
                       break;
                    case 's':
                       soll.loeschen(true);
                       break;
                    default: cout << "Nur s oder t erlaubt\n";
                }
                soll.Listenvergleich(data, muss);
                break;
            default: 
               cout << "x, a, s, k oder b sonst nichts\n";
        }
    } while (Abbruch == false);
}

void createDBSchemeifnotexists(sqlite3* db)
{
    //Wenn die Tabelle noch nicht existierte so wird sie neu angelegt
    thread Schema1([&](){sqlite3_stmt* stmt;
                         const char * stmtStr = {"create table if not exists liste(titel text, unique(titel))"};
                         sqlite3_prepare_v2(db, stmtStr, static_cast<int>(strlen(stmtStr)), &stmt, NULL);
                         if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Fehler";
                        });
    Schema1.join();
    thread Schema2([&](){sqlite3_stmt* stmt;
                         const char * stmtStr = {"create table if not exists daten(art text, menge double, einheit text, verfallsdatum integer, listid integer, foreign key (listid) references liste(rowid))"};
                         sqlite3_prepare_v2(db, stmtStr, static_cast<int>(strlen(stmtStr)), &stmt, NULL);
                         if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Fehler";
                        });
    Schema2.join();
    //Die einzelnen Listen werden angelegt. Dabei wird mit or ignore dafür gesorgt, dass sie immer nur einmal vorkommen.
    thread Liste([&](){sqlite3_stmt* stmt;
                       const char * stmtStr = {"insert or ignore into liste values(?)"};
                       sqlite3_prepare_v2(db, stmtStr, static_cast<int>(strlen(stmtStr)), &stmt, NULL);
                       sqlite3_bind_text(stmt, 1, "ist", static_cast<int>(strlen("ist")), NULL);
                       if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Fehler";
                       sqlite3_reset(stmt);
                       sqlite3_bind_text(stmt, 1, "soll", static_cast<int>(strlen("soll")), NULL);
                       if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Fehler";
                       sqlite3_reset(stmt);
                       sqlite3_bind_text(stmt, 1, "muss", static_cast<int>(strlen("muss")), NULL);
                       if(sqlite3_step(stmt) != SQLITE_DONE) cout << "Fehler";
                       });
    Liste.join();
}
