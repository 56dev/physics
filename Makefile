CC = gcc
OBJ = main.o 
T_CFLAGS = -I. -Wall -Wextra
DEPS = 
PROJECT = physics
RL_CFLAGS :=  $(shell pkg-config --cflags raylib)
RL_LIBS := $(shell pkg-config --libs raylib)
CFLAGS = $(T_CFLAGS) $(RL_CFLAGS)
LIBS = $(RL_LIBS)
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(PROJECT) $^ $(LIBS)
