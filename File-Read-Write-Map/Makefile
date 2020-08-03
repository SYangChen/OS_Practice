C=gcc -Wall
O1=read.o
O2=write.o

.SUFFIXS: .c .o

all: read write clean
	


read: $(O1)
	$(C) $(O1) -o $@

write: $(O2)
	$(C) $(O2) -o $@

dep: *.c
	$(C) -E -MM *c > depend


remove: clean
	rm read write


clean:
	rm -rf *.o depend
