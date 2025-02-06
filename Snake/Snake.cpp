#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

//initalize variables
bool snakegame;
const int width = 25;
const int height = 25;
//user variables
int x, y , spd = 1;
int tailx[100], taily[100], taillen;
//Tail cordinates 
int fposx, fposy, sposx, sposy;
//target variables
int fruitx, fruity;
//game variables
int score;
enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
directions dir;

void game_Setup() {

	snakegame = true;
	dir = STOP;
	x = rand() % width;
	y = rand() % width;
	fruitx= rand() % width;
	fruity = rand() % width;
	//Error when both fruit and player are on top
	if (x == fruitx && y == fruity) {
		x = rand() % width;
		y = rand() % width;
		fruitx = rand() % width;
		fruity = rand() % width;
	 }
	score = 0;
}

void game_Window(){
	
	system("cls");
	// top border
	for (int i = 0; i < width; i++) {
		cout <<"|"; 
	}
	cout << endl;

	//body
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (j == 0 || j == width - 1) {
				cout <<"|";
			}
			else if (i == y && j == x) {
				cout <<"3";
			}
			else if (i == fruity && j == fruitx) {
				cout <<"O";
			}
			else {
				bool tail = false; 
				for (int k = 0; k < taillen; k++) {
					if (j == tailx[k] && i == taily[k]) {
						cout << "=";
						tail = true;
					}
				}
				if (!tail) {
					cout << " ";
				}
			}
		}
		cout << endl; 
	}
	//bottom border
	for (int i = 0; i < width; i++) {
		cout <<"|";
	}
	cout << endl;
	cout << score;
	
}

void game_Input(){
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir != RIGHT) {
				dir = LEFT;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 'q':
			snakegame = false;
			break;
		}
	}
}
  
void game_Program(){

	//Tail
	fposx = tailx[0];
	fposy = taily[0];
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < taillen; i++) {
		sposx = tailx[i];
		sposy = taily[i];
		tailx[i] = fposx;
		taily[i] = fposy;
		fposx = sposx;
		fposy = sposy;
	}

	//move snake
	switch (dir) {
	case LEFT:
		x -= spd;
		break;
	case UP:
		y -= spd;
		break;
	case DOWN:
		y += spd;
		break;
	case RIGHT:
		x += spd;
		break;
	}
	//snake boarder hit
	if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
		snakegame = false;
	}

	//snake tail hit
	for ( int i = 0; i < taillen; i++ ) {
		if (x == tailx[i] && taily[i])
		{
			snakegame = false;
		}
	}

	// if snake eats fruit
	if (x == fruitx && y == fruity) {
		fruitx = rand() % width;
		fruity = rand() % width;
		score++;
		taillen++;
	}
}

int main() {
	game_Setup();
	while (snakegame == true) {
		game_Window();
		game_Input();
		game_Program();
	}	
	Sleep(30);
}