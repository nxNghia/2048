CC=g++
CFLAGS=-I.
DEPS = Game.h Graphic.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o Game.o Graphic.o
	$(CC) -o main main.o Game.o Graphic.o -lglut -lGLU -lGL -I.