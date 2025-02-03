all:
	gcc GameOfLife.c -o GameOfLife `sdl2-config --cflags --libs`