#include <stdio.h> 
#include <ncurses.h> 
#include <unistd.h>
#include <string.h>

typedef struct Ball{ 
	unsigned int cor_y; 
	int deltaX, deltaY, cor_x; 
} Ball;

typedef struct Racket{ 
	unsigned int size, pos_x, pos_y; 
} Racket;

typedef struct Score{ 
	unsigned int pos_x, pos_y; 
	int value; 
	} Score;

void invertDeltaY(Ball*); 
void invertDeltaX(Ball*);
int menu(int, int);
int gameLoop(int , int );

int menu(int m_x, int m_y){

	char *disptxt = "Welcome to PingCong!";

	attron(A_BOLD);
	mvprintw(m_y*0.25, (m_x - strlen(disptxt))*0.5, disptxt);
	attroff(A_BOLD);
	attron(A_STANDOUT);
	attron(A_BLINK);
	mvprintw(m_y*0.5, (m_x - strlen("START"))*0.5 - strlen("QUIT"), "START");
	attroff(A_BLINK);
	attroff(A_STANDOUT);
	mvprintw(m_y*0.5, (m_x - strlen("QUIT"))*0.5 + strlen("START"), "QUIT");
	refresh();
        nodelay(stdscr, 0);	
	bool menuActive = 1;
	int selected = 0;
	int key = 0;
	while(menuActive){
		key = getch();
		if(key == '\n'){menuActive = 0;}
		else if(key == KEY_RIGHT && selected < 1){
			selected++;
			clear();
			attron(A_BOLD);
			mvprintw(m_y*0.25, (m_x - strlen(disptxt))*0.5, disptxt);
			attroff(A_BOLD);
			attron(A_STANDOUT);
			attron(A_BLINK);
			mvprintw(m_y*0.5, (m_x - strlen("QUIT"))*0.5 + strlen("START"), "QUIT");
			attroff(A_BLINK);
			attroff(A_STANDOUT);
			mvprintw(m_y*0.5, (m_x - strlen("START"))*0.5 - strlen("QUIT"), "START");
			refresh();
		}
		else if(key == KEY_LEFT&& selected > 0){
			selected--;
			clear();
			attron(A_BOLD);
			mvprintw(m_y*0.25, (m_x - strlen(disptxt))*0.5, disptxt);
			attroff(A_BOLD);
			attron(A_STANDOUT);
			attron(A_BLINK);
			mvprintw(m_y*0.5, (m_x - strlen("START"))*0.5 - strlen("QUIT"), "START");
			attroff(A_BLINK);
			attroff(A_STANDOUT);
			mvprintw(m_y*0.5, (m_x - strlen("QUIT"))*0.5 + strlen("START"), "QUIT");
			refresh();
		}
	}
	return selected;
}

int main(){
	//declare some stuff
	int m_x, m_y; //max_{x,y} 
	int selection = 0;

	initscr(); //Set-up all screen stuffs
	noecho();
	curs_set(FALSE); 
	keypad(stdscr, 1);

	getmaxyx(stdscr, m_y, m_x); // How much is the screen?  
	m_x--; // It's 1 too many, if not doing this text falls of the screen m_y--;
	
	while(selection != 1){
		selection = menu(m_x, m_y);
		if(selection == 1){
			endwin();
			return 0;}
		gameLoop(m_x, m_y);
	}
	return 0;
}

int gameLoop(int m_x, int m_y){
	struct Ball GameBall; 
		struct Racket leftRacket, rightRacket; 
		struct Score leftScore, rightScore; 
		bool active = 1; 
		int input_char;

		//Now let's create the Ball
		GameBall.deltaX = -10; 
		GameBall.deltaY = 10; 
		GameBall.cor_x = m_x/2;
		//Set to somewhat of the middle of the screen 
		GameBall.cor_y = m_y/2;

		//Set-up the rackets
		leftRacket.size = m_y/10; //set right size, for both of them
		if(leftRacket.size < 3){leftRacket.size = 3;}
		rightRacket.size = leftRacket.size; 
		leftRacket.pos_y = m_y/2; //somewhat middle of y 
		rightRacket.pos_y = leftRacket.pos_y;
		leftRacket.pos_x = 1; 
		rightRacket.pos_x = m_x - 1;

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
		mvprintw(m_y/2+1, m_x/2,"%d", leftRacket.pos_y); 
		mvprintw(m_y/2-1, m_x/2, "%d", leftRacket.pos_x);
		*/
		//Print the rackets
		for(int i = 0; i < leftRacket.size; i++){
			 mvprintw(leftRacket.pos_y-i, leftRacket.pos_x, "|"); 
			 mvprintw(rightRacket.pos_y-i, rightRacket.pos_x, "|"); 
		}
		
		//Print the Scoreboard
		mvprintw(leftScore.pos_y, leftScore.pos_x, "%d", leftScore.value);
		mvprintw(rightScore.pos_y, rightScore.pos_x, "%d", rightScore.value);

		mvprintw(GameBall.cor_y, GameBall.cor_x, "O"); //Now show the the Ball at the initial Position 
		border('X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'); //Add border around screen
		refresh(); // Show first screen 
		nodelay(stdscr, 1); //FastInput, would be funny if you had to input a keystroke before the game continues...
		while(active){
			clear(); 
			input_char = getch(); 
			//let's process the input
			if(input_char ==
			KEY_UP){
				rightRacket.pos_y--; } else if(input_char == 
			KEY_DOWN){
				rightRacket.pos_y++;
			} else if(input_char == 
			'w') {leftRacket.pos_y--;} else if(input_char == 
			's') {leftRacket.pos_y++;}
			while(getch() != ERR){};
			input_char = 0;
			mvprintw(GameBall.cor_y, GameBall.cor_x, "O"); //show selected key
			for(int i = 0; i < leftRacket.size; i++){ // show dem racklette
				 mvprintw(leftRacket.pos_y-i, leftRacket.pos_x, "|"); 
				 mvprintw(rightRacket.pos_y-i, rightRacket.pos_x, "|"); 
			}
			border('X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'); //Add border around screen
			mvprintw(leftScore.pos_y, leftScore.pos_x, "%d", leftScore.value); //Scoreboard also wants to be there
			mvprintw(rightScore.pos_y, rightScore.pos_x, "%d", rightScore.value);	
			//Check for GameBall collisions
			if((GameBall.cor_x == leftRacket.pos_x && GameBall.cor_y > leftRacket.pos_y-leftRacket.size && GameBall.cor_y <= leftRacket.pos_y) || (GameBall.cor_x == rightRacket.pos_x && GameBall.cor_y > rightRacket.pos_y-rightRacket.size && GameBall.cor_y <= rightRacket.pos_y)){
				invertDeltaX(&GameBall);} 
			if(GameBall.cor_x > m_x){ leftScore.value++; GameBall.cor_y = m_y/2; GameBall.cor_x = m_x/2; }
			if(GameBall.cor_x < 0){ rightScore.value++; GameBall.cor_y = m_y/2; GameBall.cor_x = m_x/2; }
			if(GameBall.cor_y >= (m_y - 2) || GameBall.cor_y <= 1){ //let the ball bounce up and down
				invertDeltaY(&GameBall);}	
			//Update GameBall cords
			GameBall.cor_y += GameBall.deltaY/10;
			GameBall.cor_x += GameBall.deltaX/10;
			refresh();
			napms(100);
		}	

}

void invertDeltaX(Ball *ball){
	ball->deltaX = -ball->deltaX;
}
void invertDeltaY(Ball *ball){
	ball->deltaY = -ball->deltaY;
}
