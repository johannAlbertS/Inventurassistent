# Inventurassistent
## Zweck
Dieses Projekt ist dazu gedacht um
1. Den Überblick über den Inhalt der Tiefkühltruhe zu behalten
2. Sich auf Basis von Sollbeständen Einkaufslisten erstellen zu lassen

## Wie man es kriegt
### Programm an sich
Man klone das Repository mittels ```git clone https://github.com/johannAlbertS/Inventurassistent``` in einen beliebigen
Ordner. 

Dort ist dann ```make``` bzw. ```make Inventurassistent``` aus zu führen. 

### Die Datenbank
Es muss SQLite in Version 3 installiert sein. 
Unter Arch Linux z.B. ```pacman -S sqlite``` 
Zum aufsetzen des Datenschema unter Linux muss nur das Skript ```Database.sh``` ausgefürhrt werden. 
Wer einen solchen Weg für Windows kennt kann doch vielleicht eine entsprechende ```.bat``` oder ```.ps``` Datei erstellen und einen Pull-Request fertigmachen. 

## Nutzung
Unter Linux lässt sich die ausführbare Datei mittels ```./Inventurassistent``` aufrufen. Das Programm brauch allerdings noch 
Argumente. Im einfachsten Fall führt man mit ```./Inventurassistent i``` den interaktiven Modus aus. 
Über weitere Optionen informiert ```./Inventurassistent help```.