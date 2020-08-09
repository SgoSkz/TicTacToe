#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#define clear "cls"
#else
#include <unistd.h>
#define clear "clear"
#endif

// Created a struct for later use
struct Map {
	int x;
	int y;
};

// Match map for single digits to x and y
struct Map map[9];
// Variable determining which number the player chose
int chose;
// TicTacToe board
char board[3][3] = 
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
};

// Prints the TicTacToe board
void printBoard() {
	// Clear the screen based off the system
	// See #define clear
	system(clear);
	// Use for loops to print out the board in 2 dimensions
	// y dimension
	for(int i = 0; i < sizeof(board[0])/sizeof(board[0][0]); ++i) {
		// x dimension
		for(int j = 0; j < sizeof(board)/sizeof(board[0]); ++j) {
			// Middle row follows this pattern
			if( j == 1) {
				// |P| where P is either a number, X, or O
				printf("|%c|", board[i][j]);
			}
			else {
				// P where P is either a number, X, or O
				printf("%c", board[i][j]);
			}
		}
		// As long as its not the last print, print pattern -+-+-
		if( i != 2){
			printf("\n-+-+-\n");
		}
		// Last line will just print \n AKA line feed/new line
		else {
			printf("\n");
		}
	}
}

// Update the board after asking which area player would like to take
void updateBoard(char x) {
	// Do this first, then loop if expression in while returns true
	do {
		// Show the avail spaces and corresponding number
		printBoard();
		// Ask
		printf("Player %c: What space would you like to take? (1-9)\n");
		// Scan for a number
		scanf("%d", &chose);
	}
	// If the said number is already taken or is lower than 1 or greater than 9, loop
	while(chose < 1 || chose > 9 || board[map[chose-1].y][map[chose-1].x] == 'X' || board[map[chose-1].y][map[chose-1].x] == 'O');
	// Debug uses
	printf("%d%d\n", map[chose-1].y, map[chose-1].x);
	// Set the char for area chosen
	board[map[chose-1].y][map[chose-1].x] = x;
}

// Who won?
int checkWin() {
	// Clear screen
	system(clear);
	// loop from 0 to 2
	for(int i = 0; i < 3; i++) {
		// Check horizontal and vertical
		// If all are the same vertically ==> win condition
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			printf("%c wins\n", board[i][0]);
			return 1;
		}
		// If all are the same horizontally ==> win condition
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			printf("%c wins\n", board[0][i]);
			return 1;
		}
	}
	// Diagonal win condition
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		printf("%c wins\n", board[1][1]);
		return 1;
	}
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
		printf("%c wins\n", board[1][1]);
		return 1;
	}
	// No win condition, continue playing
	return 0;
}

// Main function
int main(int argc, char ** argv) {
	// Set correct mapping for Map map
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			// counting upwards from 0-8
			int k = i*3+j;
			map[k].y = i;
			map[k].x = j;
		}
	}
	// determines when to stop game
	int turns = 0;
	// Loop until condition no longer true
	while(turns < 9) {
		printBoard();
		// Toggle between player X and player O
		switch (turns%2) {
			case 0:
				updateBoard('O');
				break;
			case 1:
				updateBoard('X');
				break;
		}
		printBoard();
		// If there is a win, stop the loop no matter turn count
		if(checkWin()) {
			break;
		}
		// Turn count goes up
		turns+=1;
	}
}
