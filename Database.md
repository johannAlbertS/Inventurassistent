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