
CC = clang
CFLAGS = -c -g -Wall -Wextra
LFLAGS = -Wall -Wextra

all: natural_selection_simulator
clean:
	rm -f natural_selection_simulator *.o

natural_selection_simulator: main.o terminal_display.o structures.o
	${CC} ${LFLAGS} main.o terminal_display.o structures.o -o natural_selection_simulator

main.o: main.c
	${CC} ${CFLAGS} main.c -o main.o

terminal_display.o: terminal_display.c
	${CC} ${CFLAGS} terminal_display.c -o terminal_display.o

structures.o: structures.c
	${CC} ${CFLAGS} structures.c -o structures.o
