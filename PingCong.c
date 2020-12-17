#include <stdio.h>
#include<ncurses.h>

typedef struct Ball{
	unsigned int cor_x, cor_y;
	int deltaX, deltaY;

} Ball;

typedef struct Racket{
	unsigned int size, pos_x, pos_y;
} Racket;

typedef struct Score{
	unsigned int pos_x, pos_y;
	int value;
} Score;

void invertDeltaY(Ball);
void invertDeltaX(Ball);

int main(){
	//declare some stuff
	int m_x, m_y; //max_{x,y}
	struct Ball GameBall; 
	struct Racket leftRacket, rightRacket;
	struct Score leftScore, rightScore;

	printf("Hello World!");
	initscr(); //Set-up all screen stuffs
	nodelay(stdscr, 1);
	curs_set(FALSE);
	keypad(stdscr, 1);
	border('X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'); //Add border around screen

	getmaxyx(stdscr, m_y, m_x); // How much is the screen?
	m_x--; // It's 1 too many, if not doing this text falls of the screen
	m_y--;
	//Now let's create the Ball
	GameBall.deltaX = 10;
	GameBall.deltaY = 0;
	GameBall.cor_x = m_x/2; //Set to somewhat of the middle of the screen
	GameBall.cor_y = m_y/2;
	mvprintw(GameBall.cor_y, GameBall.cor_x, "O"); //Now show the the Ball at the initial Position

	//Now set-up the rackets
	leftRacket.size = m_y/10; //set right size, for both of them
	rightRacket.size = leftRacket.size;
	leftRacket.pos_y = m_y/2; //somewhat middle of y
	rightRacket.pos_y = leftRacket.pos_y;
	leftRacket.pos_x = 0;
	rightRacket.pos_x = m_x;

	//Add the scoreboard
	leftScore.pos_x = 0.25*m_x;
	leftScore.pos_y = 1;
	leftScore.value = 0;
	rightScore.pos_x = 0.75*m_x;
	rightScore.pos_y = 1;
	rightScore.value = 0;
	
	//Print some cool stats about the left racket 
	/*
	mvprintw(m_y/2, m_x/2, "%d", leftRacket.size);
	mvprintw(m_y/2+1, m_x/2, "%d", leftRacket.pos_y);
	mvprintw(m_y/2-1, m_x/2, "%d", leftRacket.pos_x);
	*/
	//Print the rackets
	for(int i = 0; i < leftRacket.size; i++){
		mvprintw(leftRacket.pos_y-i, leftRacket.pos_x, "|");
		mvprintw(rightRacket.pos_y-i, rightRacket.pos_x-1, "|");
		continue;
	}
	//Print the Scoreboard
	mvprintw(leftScore.pos_y, leftScore.pos_x, "%d", leftScore.value);
	mvprintw(rightScore.pos_y, rightScore.pos_x, "%d", rightScore.value);
	refresh(); // Show first screen
	sleep(10000);
	return 0;
}

void invertDeltaX(Ball ball){
	ball.deltaX = -ball.deltaX;
}
void invertDeltaY(Ball ball){
	ball.deltaY = -ball.deltaY;
}
