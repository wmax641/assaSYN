CC=g++
CFLAGS=-O
LFLAGS= -lm -lcrypto
OBJ= assaSYN.o Layer3_ip.o Layer4_tcp.o ip_helper.o

main: ${OBJ}
	$(CC) -g -o $@ $^ $(LFLAGS) 

assaSYN.o: assaSYN.cpp Layer3_ip.cpp Layer4_tcp.cpp
	$(CC) -g -c $(CFLAGS) $<

Layer3_ip.o: Layer3_ip.cpp ip_helper.c
	$(CC) -g -c $(CFLAGS) $<

Layer4_tcp.o: Layer4_tcp.cpp ip_helper.c
	$(CC) -g -c $(CFLAGS) $<

ip_helper.o: ip_helper.c
	$(CC) -g -c $(CFLAGS) $<


.PHONY: clean

clean:
	rm *.o
