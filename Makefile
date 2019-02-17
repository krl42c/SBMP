OBJS = src/play.c src/play.h src/main.c

CC = gcc

COMPILER_FLAGS = -Wall -Wextra -Wpedantic

LINKER_FLAGS = -lSDL2 -lSDL2_mixer -lncurses

OBJ_NAME = sbmp

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
