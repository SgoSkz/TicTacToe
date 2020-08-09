#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#define clear "cls"
#else
#include <unistd.h>
#define clear "clear"
#endif

struct Map {
	int x;
	int y;
};

struct Map map[9];
int chose;
char board[3][3] = 
{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
};

void printBoard() {
	system(clear);
	for(int i = 0; i < sizeof(board[0])/sizeof(board[0][0]); ++i) {
		for(int j = 0; j < sizeof(board)/sizeof(board[0]); ++j) {
			if( j == 1) {
				printf("|%c|", board[i][j]);
			}
			else {
				printf("%c", board[i][j]);
			}
		}
		if( i != 2){
			printf("\n-+-+-\n");
		}
		else {
			printf("\n");
		}
	}
}

void updateBoard(char x) {
	do {
		printBoard();
		printf("Player %c: What space would you like to take? (1-9)\n");
		scanf("%d", &chose);
	}
	while(chose < 1 || chose > 9 || board[map[chose-1].y][map[chose-1].x] == 'X' || board[map[chose-1].y][map[chose-1].x] == 'O');
	printf("%d%d\n", map[chose-1].y, map[chose-1].x);
	board[map[chose-1].y][map[chose-1].x] = x;
}

int checkWin() {
	system(clear);
	for(int i = 0; i < 3; i++) {
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			printf("%c wins\n", board[i][0]);
			return 1;
		}
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			printf("%c wins\n", board[0][i]);
			return 1;
		}
	}
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		printf("%c wins\n", board[1][1]);
		return 1;
	}
	if(board[0][2] == board[1][1] && board[0][0] == board[2][0]) {
		printf("%c wins\n", board[1][1]);
		return 1;
	}
	return 0;
}

int main(int argc, char ** argv) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			int k = i*3+j;
			map[k].y = i;
			map[k].x = j;
		}
	}
	int turns = 0;
	while(turns < 9) {
		printBoard();
		switch (turns%2) {
			case 0:
				updateBoard('O');
				break;
			case 1:
				updateBoard('X');
				break;
		}
		printBoard();
		if(checkWin()) {
			break;
		}
		turns+=1;
	}
}
