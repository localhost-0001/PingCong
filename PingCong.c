#include <stdio.h>
#include<ncurses.h>

typedef struct Ball{
	unsigned int cor_x, cor_y;
	int deltaX, deltaY;

} Ball;

int main(){
	//declare some stuff
	int m_x, m_y; //max_{x,y}

	printf("Hello World!");
	initscr(); //Set-up all screen stuffs
	nodelay(stdscr, 1);
	curs_set(FALSE);
	keypad(stdscr, 1);
	border('X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'); //Add border around screen

	getmaxyx(stdscr, m_y, m_x); // How much is the screen?

	//Now let's create the Ball
	struct Ball GameBall; 
	GameBall.deltaX = 10;
	GameBall.deltaY = 0;
	GameBall.cor_x = m_x/2; //Set to somewhat of the middle of the screen
	GameBall.cor_y = m_y/2;
	mvprintw(GameBall.cor_y, GameBall.cor_x, "O"); //Now show the the Ball at the initial Position

	refresh(); // Show first screen
	sleep(10000);
	return 0;
}

void invertDeltaX(Ball ball){
	ball.deltaX = -ball.deltaX;
}
