all:
	gcc -I . GameOfLife.c -o GameOfLife `sdl2-config --cflags --libs`