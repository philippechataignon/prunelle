CC=g++
CXX=g++
CXXFLAGS=-O2 -pipe -fomit-frame-pointer
LDD=g++

# OBJ = prunelle.o globals.o lien.o lien_elem.o matflux.o valeur.o element.o commune.o
OBJ = prunelle.o options.o utils.o lien.o liens.o matflux.o valeur.o element.o commune.o
OBJTEST = test.o matflux.o valeur.o element.o
OBJPREP = prepare_flux.o matflux.o valeur.o element.o commune.o

all:prunelle test prepare_flux
prunelle: $(OBJ)
test:     $(OBJTEST)
prep: prepare_flux
prepare_flux: $(OBJPREP)

commune.o: commune.h element.h
lien.o: lien.h commune.h matflux.h
liens.o: liens.h commune.h matflux.h
matflux.o: matflux.h valeur.h options.h 
prepare_flux.o: commune.h matflux.h
prunelle.o: lien.h liens.h commune.h matflux.h options.h utils.h globals.h
test.o: matflux.h
utils.o: commune.h matflux.h lien.h utils.h
valeur.o: valeur.h

clean:
	-rm -rf $(OBJ) $(OBJTEST) $(OBJPREP) *.obj *~ prunelle test prepare_flux
