CC = g++
TARGET1 = DiningPhilosophers

FLAG = -Wall -std=c++11 -pthread

all: $(TARGET1).cpp
	$(CC) $(FLAG) -c $(TARGET1).cpp
	$(CC) $(FLAG) -o $(TARGET1) $(TARGET1).o 
	
clean:
	rm -f $(TARGET1)
	rm -f $(TARGET1).o
	
