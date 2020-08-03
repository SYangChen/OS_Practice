CC = gcc
TARGET1 = DiningPhy

FLAG = -Wall -std=c11 -pthread

all: $(TARGET1).c
	$(CC) $(FLAG) -c $(TARGET1).c
	$(CC) $(FLAG) -o $(TARGET1) $(TARGET1).o 
	
clean:
	rm -f $(TARGET1)
	rm -f $(TARGET1).o
	
