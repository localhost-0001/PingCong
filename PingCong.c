#include <stdio.h>

int main(){
	printf("Hello World!");
	initscr();
	nodelay(stdscr, 1);
	curs_set(FALSE);
	keypad(stdscr, 1);
	refresh();
	sleep(1);
	
	

	return 0;
}
