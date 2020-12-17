#include <stdio.h>
#include<ncurses.h>

typedef struct{
	unsigned int cor_x, cor_y;
	int deltaX, deltaY;
} Ball;


int main(){
	printf("Hello World!");
	initscr();
	nodelay(stdscr, 1);
	curs_set(FALSE);
	keypad(stdscr, 1);
	refresh();
	return 0;
}
