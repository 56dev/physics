CC = gcc
IDIR = ../include
ODIR = ../obj
T_CFLAGS = -I$(IDIR) -Wall -Wextra
_DEPS = 
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))
_OBJ = main.o 
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
PROJECT = ../physics
RL_CFLAGS :=  $(shell pkg-config --cflags raylib)
RL_LIBS := $(shell pkg-config --libs raylib)
CFLAGS = $(T_CFLAGS) $(RL_CFLAGS)
LIBS = $(RL_LIBS)


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(PROJECT) $^ $(LIBS)
