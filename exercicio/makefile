
CC = gcc

CFLAGS = -g -Wall 
TARGETS	 = write_texts

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)

run:
	./write_texts < input.txt && cat texts.bin

crun:
	
	make
	make run