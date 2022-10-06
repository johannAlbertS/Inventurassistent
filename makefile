all: Inventurassistent

Inventurassistent: main.o Funktionen.o Klasse.o
	g++ Funktionen.o Klasse.o main.o -o Inventurassistent

main.o: main.cpp Funktionen.h
	g++ -c main.cpp

Klasse.o: Klasse.cpp Klasse.h
	g++ -c Klasse.cpp

Funktionen.o: Funktionen.cpp Funktionen.h
	g++ -c Funktionen.cpp

clean:
	rm -rf *o Inventurassistent
