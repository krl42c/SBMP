OBJS = src/play.cc

CC = g++

COMPILER_FLAGS = -Wall -Wextra -Wpedantic -std=c++17 -O2

LINKER_FLAGS = -lSDL2 -lSDL2_mixer -lncurses -lpthread -lstdc++fs 

OBJ_NAME = sbmp

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
