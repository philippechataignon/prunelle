CC=g++
CPPFLAGS=-O2 -pipe -fomit-frame-pointer

OBJECTS = commune.o  ent.o  flux.o  listeent.o  listeflux.o  prunelle.o
HEADERS = commune.h  ent.h  flux.h  listeent.h  listeflux.h  prunelle.h

prunelle: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o prunelle 

$(OBJECTS): $(HEADERS)
listeflux.o:  outils.h

clean:
	rm $(OBJECTS) prunelle
