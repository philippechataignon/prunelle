CC=g++
CPPFLAGS=-O2 -march=athlon-xp -pipe -fomit-frame-pointer

OBJ = prunelle.o globals.o matflux.o valeur.o element.o commune.o
OBJTEST = test.o matflux.o valeur.o element.o
OBJPREP = prepare_flux.o matflux.o valeur.o element.o commune.o

all:prunelle test prepare_flux
prunelle: $(OBJ)
test:     $(OBJTEST)
prep: prepare_flux
prepare_flux: $(OBJPREP)

prunelle.o: globals.h

clean:
	-rm $(OBJ) $(OBJTEST) prunelle test prepare_flux 
