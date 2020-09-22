OBJS = HashTable.o askisi2.o
SOURCE = HashTable.c askisi2.c
HEADER = HashTable.h askisi2.h
OUT = ergasia2
CC = gcc
FLAGS = -g -c 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

askisi2.o: askisi2.c
	$(CC) $(FLAGS) askisi2.c

HashTable.o: HashTable.c
	$(CC) $(FLAGS) HashTable.c

clean:
	rn -f $(OBJS) $(OUT)
