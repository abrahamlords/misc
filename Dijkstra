OBJS = dijkstra.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

proj3: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o dijkstra

dijkstra.o: main.cpp heap.cpp graph.cpp util.cpp
	$(CC) $(CFLAGS) main.cpp -o dijkstra.o

clean:
	\rm *.o dijkstra
