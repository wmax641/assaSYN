CC=g++
CFLAGS=-O
LFLAGS= -lm -lcrypto
OBJ= assaSYN.o Packet3.o ip_helper.o

main: ${OBJ}
	$(CC) -g -o $@ $^ $(LFLAGS) 

assaSYN.o: assaSYN.cpp Packet3.cpp 
	$(CC) -g -c $(CFLAGS) $<

Packet3.o: Packet3.cpp ip_helper.c
	$(CC) -g -c $(CFLAGS) $<

ip_helper.o: ip_helper.c
	$(CC) -g -c $(CFLAGS) $<


.PHONY: clean

clean:
	rm *.o
