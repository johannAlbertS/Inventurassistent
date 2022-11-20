#include <iostream>
#include <sqlite3.h>
#include "Datahandling/Listenobjekt.h"
using namespace std;

#ifndef __FUNKTIONEN_H__
#define __FUNKTIONEN_H__
void help();
void interactivemode(Listenfunktionen&, Listenfunktionen&, Listenfunktionen&);
void createDBSchemeifnotexists(sqlite3*);
#endif