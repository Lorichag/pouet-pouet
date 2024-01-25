all: exec clean

main.o: main.c fonctions.h
 gcc -c main.c -o main.o

fonctionsT.o: fonctionsT.c fonctions.h
 gcc -c fonctionsT.c -o fonctionsT.o

fonctionsS.o: fonctionsS.c fonctions.h
 gcc -c fonctionsS.c -o fonctionsS.o

exec: fonctions.o main.o
	gcc fonctions.o main.o -o exec
clean:
	rm *.o
