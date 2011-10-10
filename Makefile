CC=gcc
CFLAGS=-Wall -g
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

.PHONY: doc clean

all : wordstat 

wordstat : $(OBJS)
	$(CC) $(OBJS) -o $@

.c.o : $(SRCS)
	$(CC) -g -c $(CFLAGS) $*.c

clean : 
	rm -rf *.o *.a wordstat
	rm -rf readme.aux
	rm -rf readme.log

doc :
	pdflatex readme.tex
    
