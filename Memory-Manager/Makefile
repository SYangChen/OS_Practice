C=gcc -Wall
O1=main.o mm.o

.SUFFIXS: .c .o

all: main clean

main: $(O1)
	$(C) $(O1) -o $@

dep: *.c
	$(C) -E -MM *c > depend

remove: clean
	rm main

clean:
	rm -rf *.o depend
