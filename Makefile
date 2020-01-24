LIBS = -lglut -lGLU -lGL -lm
LOCATEGLUT = -I ./GL
CC = gcc
CFLAGS = -Wall -g
NOMAPP = Projet_Chlamydomonas
FICHIERS = chlamy.o project.o graphic.o options.o easter_egg.o

$(NOMAPP):	$(FICHIERS)
	@ $(CC) $(CFLAGS) -o $(@) $(^) $(LIBS)

project.o:	project.c structures.h headers.h
	@ $(CC) $(CFLAGS) -c $(@:.o=.c) $(LOCATEGLUT)

graphic.o:	graphic.c structures.h globales.h
	@ $(CC) $(CFLAGS) -c $(@:.o=.c) $(LOCATEGLUT)

chlamy.o:	chlamy.c globales.h structures.h headers.h
	@ $(CC) $(CFLAGS) -c $(@:.o=.c)

options.o:	options.c structures.h globales.h headers.h
	@ $(CC) $(CFLAGS) -c $(@:.o=.c) $(LOCATEGLUT)

easter_egg.o:	easter_egg.c
	@ $(CC) $(CFLAGS) -c $(@:.o=.c) $(LOCATEGLUT)

clean:	
	@ rm -rf *.o $(NOMAPP)



#CFLAGS = -Wall
#CC=gcc
#SRC = $(wildcard *.c)
#OBJ = ${SRC:.c=.o}
#LIBS = -lglut -lGLU -lGL -lm
#EXEC = main

#main: $(OBJ)
#	${CC} $(CFLAGS) $(OBJ) -o $@ $(LIBS)
#	-rm -f ${OBJ}
#	./$(EXEC)

#%.o: %.c
#	${CC} ${CFLAGS} $(LIBS) -c $<

#.depend:
#	gcc -MM ${SOURCES_LIB} > $@
#-include .depend

#clean:
#	-rm -f ${OBJ} main