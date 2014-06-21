#--------------------------------------------------------------
# Makefile generated with cmak version 0.9.6 (4/2006).
# Date: 21/5/2014 2:51:20
#--------------------------------------------------------------

PREFIX  = /usr/local
CFLAGS  = 
LDFLAGS = -lpthread

CC = gcc
RM = rm -f
INSTALL_PROG = install -m 755 -s

EXE = ../ardrone
EXE_BASE = ardrone

LIBP = ../api/ardrone_api.a

OBJS = main.o

ALL : $(EXE)

main.o : main.c
	$(CC) -c main.c $(CFLAGS) -o main.o

$(EXE) : $(OBJS)
	$(CC) $(OBJS) $(LIBP) -o $(EXE) $(LDFLAGS)

install : $(EXE)
	$(INSTALL_PROG) $(EXE) $(PREFIX)/bin

uninstall :
	$(RM) $(PREFIX)/bin/$(EXE_BASE)

clean :
	$(RM) $(OBJS) $(EXE)