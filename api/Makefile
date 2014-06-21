#--------------------------------------------------------------
# Makefile generated with cmak version 0.9.6 (4/2006).
# Date: 21/5/2014 2:37:33
#--------------------------------------------------------------

PREFIX  = /usr/local
CFLAGS  = 
LDFLAGS = -lpthread

CC = gcc
AR = ar -r
RM = rm -f
INSTALL_PROG = install -m 755 -s

EXE = ardrone_api.a

OBJS = drone_api.o libclient.o

ALL : $(EXE)

drone_api.o : drone_api.c
	$(CC) -c drone_api.c $(CFLAGS) -o drone_api.o

libclient.o : libclient.c
	$(CC) -c libclient.c $(CFLAGS) -o libclient.o

$(EXE) : $(OBJS)
	$(AR) $(EXE) $(OBJS)

clean :
	$(RM) $(OBJS) $(EXE)