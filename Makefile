OBJS = main.o mySDL.o Boids.o
CC = g++
COMPILER_FLAGS = -std=c++11
LINKER_FLAGS = -lSDL2 -lSDL2_image
OBJ_NAME = Boids

all: main.o mySDL.o Boids.o
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: main.cpp
	$(CC) $(COMPILER_FLAGS) -c main.cpp


mySDL.o: mySDL.cpp
	$(CC) $(COMPILER_FLAGS) -c mySDL.cpp

Boids.o: Boids.cpp
	$(CC) $(COMPILER_FLAGS) -c Boids.cpp

clean: 
	rm *.o Boids