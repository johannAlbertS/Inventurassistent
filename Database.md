# Datenbank
## Welche?
Ich verwende SQLite mit dem Standard C-Interface
## Schema
Es gibt zwei Tabellen:
1. Eine Tabelle, die darstellt welcher Liste ein Datensatz zugeordnet ist. 
   - Der Liste für den Ist-Zustand ('ist')
   - Der Liste was man immer haben will ('soll')
   - Der Liste was man zum Erreichen des Sollzustandes noch braucht ('muss')
2. Und eine Tabelle mit den eigentlichen Datensätzen. Diese hat vier Spalten
   - Art
   - Menge
   - Einheit
   - Verfallsdatum
## Konkrete Umsetzung
Folgenden Befehle müssen in der Sqlite-Konsole angegeben werden um das Schema zu erzeugen
1. ```create table liste(titel text);```
2. ```create table daten(art text, menge double, einheit text, verfallsdatum integer, listid integer, foreign key (listid) references liste(rowid));```
## Nutzung
### Beispiele
- ```insert into liste values('ist');```
- ```select rowid, titel from liste;```
- ```insert into daten values ('Rindergulasch', 500, 'g', 0, 1);```
- ```select rowid, art, menge, einheit, verfallsdatum from daten;```
