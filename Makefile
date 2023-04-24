./CC = gcc 
EXEC = main

all : $(EXEC)

main: biblioLC.o entreeSortieLC.o biblioH.o entreeSortieH.o main.o
	$(CC) -Wall -o main biblioLC.o entreeSortieLC.o biblioH.o entreeSortieH.o main.o
   
biblioLC.o : biblioLC.c biblioLC.h
	$(CC) -Wall -c -o biblioLC.o biblioLC.c

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h biblioLC.h
	$(CC) -Wall -c -o entreeSortieLC.o entreeSortieLC.c

biblioH.o : biblioH.c biblioH.h
	$(CC) -Wall -c -o biblioH.o biblioH.c
	
entreeSortieH.o : entreeSortieH.c entreeSortieH.h biblioH.h
	$(CC) -Wall -c -o entreeSortieH.o entreeSortieH.c

main.o : main.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	$(CC) -Wall -c -o main.o main.c
	
clean:
	rm -f *.o $(EXEC)
	
	

