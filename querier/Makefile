# Makefile for Querier
#
# Aaron Svendsen and William Wolfe 5/9/16

PROG = querier
OBJS = querier.c orderlist.c
LIBS = -lcurl
LLIBS = ../lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build the querier
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


# querier source dependencies; add others as needed

orderlist.o:orderlist.c 

../lib/cs50ds.a:

../common/common.a:

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)



