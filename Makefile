CC=g++
PLATFORM=Linux
CFLAGS=-g -DDEBUG -D$(PLATFORM) -DUNIX -DNCURSES -Wall -Wno-unused-variable -Wno-sign-compare
#CFLAGS=-g -DDEBUG -D$(PLATFORM) -DUNIX -DNCURSES -Wno-unused-variable
#CFLAGS=-g -DDEBUG -D$(PLATFORM) -DUNIX -Wall -DXCURSES -Wno-unused-variable
#CFLAGS=-Wall -O3
#CFLAGS=-Wall -O -pg
#CFLAGS=-D$(PLATFORM)
XDIR=/usr/X11R6/lib
#CURSESLIBS=-L$(XDIR) -lXt -lXaw  -lXCurses
CURSESLIBS=-L$(XDIR) -lncurses


#LDFLAGS=-static

all	: crimesquad

#LIB=-L$(DIST)/lib/$(PLATFORM)
#INC=-I$(DIST)/include/$(PLATFORM) -I$(REUSE) -I../
crimesquad	: game.o cursesmovie.o lcsio.o compat.o
	$(CC) $(CFLAGS) $(LIB) $(LDFLAGS) -o $@ game.o cursesmovie.o lcsio.o compat.o\
	$(CURSESLIBS)
	
game.o	: game.cpp lcsio.h compat.h
	$(CC) $(CFLAGS) $(INC) -c -o $@ game.cpp
	
cursesmovie.o	: cursesmovie.cpp compat.h lcsio.h
	$(CC) $(CFLAGS) $(INC) -c -o $@ cursesmovie.cpp

lcsio.o	: lcsio.cpp lcsio.h
	$(CC) $(CFLAGS) $(INC) -c -o $@ lcsio.cpp
	
compat.o	: compat.cpp compat.h
	$(CC) $(CFLAGS) $(INC) -c -o $@ compat.cpp

