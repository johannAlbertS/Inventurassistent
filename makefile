all: Inventurassistent

Inventurassistent: main.o Datahandling/Listenobjekt.o Datahandling/Datenobjekt.o Funktionen.o
	g++ Funktionen.o Listenobjekt.o Datenobjekt.o main.o -o Inventurassistent -l sqlite3

main.o: main.cpp Funktionen.h Datahandling/Listenobjekt.h
	g++ -c main.cpp

Datahandling/Datenobjekt.o: Datahandling/Datenobjekt.cpp Datahandling/Datenobjekt.h
	g++ -c Datahandling/Datenobjekt.cpp

Datahandling/Listenobjekt.o: Datahandling/Listenobjekt.cpp Datahandling/Listenobjekt.h
	g++ -c Datahandling/Listenobjekt.cpp

Funktionen.o: Funktionen.cpp Funktionen.h
	g++ -c Funktionen.cpp

clean:
	rm -rf *o Inventurassistent
