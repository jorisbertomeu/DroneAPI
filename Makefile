#--------------------------------------------------------------
# Makefile generated with cmak version 0.9.6 (4/2006).
# Date: 21/5/2014 0:4:41
#--------------------------------------------------------------

PREFIX  = /usr/local
CFLAGS  = 
LDFLAGS = 

CC = gcc
RM = rm -f
INSTALL_PROG = install -m 755 -s

EXE = ardrone

OBJS = libclient.o main.o

ALL : $(EXE)

libclient.o : libclient.c
	$(CC) -c libclient.c $(CFLAGS) -o libclient.o

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