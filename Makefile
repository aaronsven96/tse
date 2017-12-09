# Makefile to make all parts of TSE
#
# Aaron Svendsn and William Wolfe

LIBS = -lcurl
LLIBS = ../lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build all the directories
ALL:
	cd common; $(MAKE)
	cd lib; $(MAKE)
	cd crawler; $(MAKE)
	cd indexer; $(MAKE)
	cd querier; $(MAKE)


clean:
	rm -f *~
	rm -f *.o
	cd lib; $(MAKE) clean
	cd common; $(MAKE) clean
	cd crawler; $(MAKE) clean
	cd indexer; $(MAKE) clean
	cd querier; $(MAKE) clean
