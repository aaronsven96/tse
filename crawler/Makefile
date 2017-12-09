# Makefile TEMPLATE for 'crawler' module
#
# David Kotz, April 2016

PROG = crawler
OBJS = crawler.o 
LIBS = -lcurl
LLIBS = ../lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build the crawler
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# crawler source dependencies; add others as needed 
#../lib/cs50ds.a:
#../common/common.a:
../lib/cs50ds.a:
	cd ../lib; $(MAKE)

../common/common.a:
	cd ../common $(MAKE)
clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)



