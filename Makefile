CC=g++
CPPFLAGS=-O2 -pipe -fomit-frame-pointer

OBJECTS = prunelle.o matflux.o valeur.o element.o commune.o

prunelle: $(OBJECTS)

clean:
	-rm $(OBJECTS) prunelle 
