#!/bin/bash
sqlite3 Daten.db "create table liste(titel text);"
sqlite3 Daten.db "create table daten(art text, menge double, einheit text, verfallsdatum integer, listid integer, foreign key (listid) references liste(rowid));"
sqlite3 Daten.db "insert into liste values('ist');"
sqlite3 Daten.db "insert into liste values('soll');"
sqlite3 Daten.db "insert into liste values('muss');"
