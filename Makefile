
CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags --libs sdl2`
IN = game.c main.c
OUT = -o gol

default:
	$(CC) $(IN) $(OUT) $(CFLAGS) -lm

debug: default
	./gol