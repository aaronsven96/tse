# Makefile for Indexer and Indextest
#
# Aaron Svendsen and William Wolfe 5/9/16

PROG = indexer
OBJS = indexer.o 
LIBS = -lcurl
LLIBS = ../lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build the crawler
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# build index test
Test: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# crawler source dependencies; add others as needed

../lib/cs50ds.a:

../common/common.a:

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	rm -f Test


