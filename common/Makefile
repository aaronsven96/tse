# Makefile TEMPLATE for 'cs50ds' library
#   Builds and compiles common  into a library.
#
# Aaron Svendsen 

OBJS = web.o file.o word.o


LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $@ $^

# add other targets for the other .o files

web.o: web.c web.h
file.o: file.c file.h
word.o: word.c word.h

# add cleanup commands for other subdirectories
clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIB)


