all: Inventurassistent

Inventurassistent: main.o Data/Listenobjekt.o Data/Datenobjekt.o Funktionen.o
	g++ Funktionen.o Listenobjekt.o Datenobjekt.o main.o -o Inventurassistent

main.o: main.cpp Funktionen.h
	g++ -c main.cpp

Data/Datenobjekt.o: Data/Datenobjekt.cpp Data/Datenobjekt.h
	g++ -c Data/Datenobjekt.cpp

Data/Listenobjekt.o: Data/Listenobjekt.cpp Data/Listenobjekt.h
	g++ -c Data/Listenobjekt.cpp

Funktionen.o: Funktionen.cpp Funktionen.h
	g++ -c Funktionen.cpp

clean:
	rm -rf *o Inventurassistent
