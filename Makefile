# CC=g++
# CXX=g++
# CXXFLAGS=-Os -march=athlon-xp -pipe -fomit-frame-pointer
CC=/opt/intel/compiler70/ia32/bin/icc
CXX=/opt/intel/compiler70/ia32/bin/icc
CXXFLAGS=-O2 -tpp6 -march=pentiumiii

OBJ = prunelle.o globals.o lien.o matflux.o valeur.o element.o commune.o
OBJTEST = test.o matflux.o valeur.o element.o
OBJPREP = prepare_flux.o matflux.o valeur.o element.o commune.o

all:prunelle test prepare_flux
prunelle: $(OBJ)
test:     $(OBJTEST)
prep: prepare_flux
prepare_flux: $(OBJPREP)

prunelle.o: globals.h

clean:
	-rm $(OBJ) $(OBJTEST) $(OBJPREP) *.obj *~ prunelle test prepare_flux

