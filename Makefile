CC=g++
CPPFLAGS=-O2 -pipe -fomit-frame-pointer

LIBBCC=c0x32.obj import32.lib cw32.lib

CFLAGS=-c -I.
LFLAGS=-aa -L$(LIBPATH)

OBJ = prunelle.o globals.o lien.o matflux.o valeur.o element.o commune.o
OBJTEST = test.o matflux.o valeur.o element.o
OBJPREP = prepare_flux.o matflux.o valeur.o element.o commune.o

all:prunelle test prepare_flux
prunelle: $(OBJ)
test:     $(OBJTEST)
prep: prepare_flux
prepare_flux: $(OBJPREP)
prunelle.exe: prunelle.obj globals.obj lien.obj matflux.obj valeur.obj element.obj commune.obj

prunelle.o: globals.h

clean:
	-rm $(OBJ) $(OBJTEST) $(OBJPREP) *.obj *~ prunelle test prepare_flux

