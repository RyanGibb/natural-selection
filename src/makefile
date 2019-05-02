
CC = clang
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -Wall -Wextra

all: sim
clean:
	rm -f sim *.o

sim: sim.o terminal_display.o structures.o
	${CC} ${LFLAGS} sim.o terminal_display.o structures.o -o sim

sim.o: sim.c
	${CC} ${CFLAGS} sim.c -o sim.o

terminal_display.o: terminal_display.c
	${CC} ${CFLAGS} terminal_display.c -o terminal_display.o

structures.o: structures.c
	${CC} ${CFLAGS} structures.c -o structures.o
