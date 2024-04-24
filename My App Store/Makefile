OBJS = myAppStore.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

proj2: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o myAppStore

myAppStore.o: BTree.h defn.h myAppStore.cpp
	$(CC) $(CFLAGS) myAppStore.cpp -o myAppStore.o

clean:
	\rm *.o myAppStore