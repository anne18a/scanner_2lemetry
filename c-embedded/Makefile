SRC=src
INC=include
LIB=.
CLIENT=client

CC=gcc
CCFLAGS=-I$(INC) -Wall -O
LDFLAGS=-L$(LIB) -lemqtt
AR=ar


c: $(CLIENT)/example

$(CLIENT)/example: libemqtt.a example.o
	$(CC) example.o -o $(CLIENT)/example $(LDFLAGS)

example.o: $(CLIENT)/example.c $(INC)/libemqtt.h
	$(CC) $(CCFLAGS) -c $(CLIENT)/example.c -o example.o

libemqtt.a: libemqtt.o
	$(AR) rcs libemqtt.a libemqtt.o

libemqtt.o: $(SRC)/libemqtt.c $(INC)/libemqtt.h
	$(CC) $(CCFLAGS) -c $(SRC)/libemqtt.c -o libemqtt.o

all: c

clean:
	rm -f *.o libemqtt.a
	rm -f $(CLIENT)/example

