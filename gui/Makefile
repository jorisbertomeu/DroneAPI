#--------------------------------------------------------------
# Makefile generated with cmak version 0.9.6 (4/2006).
# Date: 21/5/2014 16:17:38
#--------------------------------------------------------------

PREFIX  = /usr/local
CFLAGS  = `pkg-config --libs --cflags gtk+-2.0`
LDFLAGS = `pkg-config --libs --cflags gtk+-2.0`

CC = gcc
RM = rm -f
INSTALL_PROG = install -m 755 -s

EXE = gui

OBJS = main.o

ALL : $(EXE)

main.o : main.c
	$(CC) -c main.c $(CFLAGS) -o main.o

$(EXE) : $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LDFLAGS)

install : $(EXE)
	$(INSTALL_PROG) $(EXE) $(PREFIX)/bin

uninstall :
	$(RM) $(PREFIX)/bin/$(EXE)

clean :
	$(RM) $(OBJS) $(EXE)