#CC=g++-3.4
#CXX=g++-3.4
#CXXFLAGS=-O2 -pipe -fomit-frame-pointer
#LDD=g++
# CXXFLAGS=-O2 -march=athlon-xp -pipe -g
CC=/opt/intel/compiler81/bin/icc
CXX=/opt/intel/compiler81/bin/icc
CXXFLAGS=-O3 -axK -xK -tpp6   -march=pentiumiii
# # CXXFLAGS=-O2
#LDFLAGS=-static-libcxa
# LDFLAGS=-cxxlib-gcc -gcc-name=g++

# OBJ = prunelle.o globals.o lien.o lien_elem.o matflux.o valeur.o element.o commune.o
OBJ = prunelle.o options.o utils.o lien.o liens.o matflux.o valeur.o element.o commune.o
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

