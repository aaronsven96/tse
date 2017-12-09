# Makefile TEMPLATE for 'cs50ds' library
#   Builds and compiles all the data structures into a library.
#
# David Kotz, April 2016 edited by Aaron

OBJS = memory/memory.o bag/bag.o hashtable/hashtable.o hashtable/jhash.o hashtable/list.o counters/counters.o
LIB = cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $@ $^

# add other targets for the other .o files

memory/memory.o: memory/memory.c memory/memory.h
	cd memory; $(MAKE) memory.o
bag/bag.o: bag/bag.c bag/bag.h
	cd bag; $(MAKE) bag.o
hashtable/hashtbale.o: hashtable/hashtable.c hashtable/hashtable.h
	cd hashtable; $(MAKE) hashtable.o
hashtable/list.o: hashtable/list.c hashtable/list.h
	cd hashtable; $(MAKE) list.o
hashtable/jhash.o: hashtable/jhash.c hashtable/jhash.h
	cd hashtable; $(MAKE) jhash.o
counters/counters.o: counters/counters.c counters/counters.h
	cd counters; $(MAKE) counters.o

# add cleanup commands for other subdirectories
clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIB)
	cd memory; $(MAKE) $@
	cd bag; $(MAKE) $@
	cd hashtable; $(MAKE) $@
	cd list; $(MAKE) $@
	cd counters; $(MAKE) $@
