#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINES 15

int board[SIZE][SIZE];
int revealed[SIZE][SIZE];
int revealedBoard[SIZE][SIZE];

void initializeBoard() {
    // 보드 초기화
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
            revealed[i][j] = 0;
        }
    }

    // 랜덤하게 지뢰 배치
    srand(time(NULL));
    for (int i = 0; i < MINES; i++) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        board[x][y] = -1;
    }
	
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(board[i][j] != -1){
				if(i == 0){
					if(j == 0){
						revealedBoard[i][j] = (board[i + 1][j] + board[i][j + 1] + board[i + 1][j + 1]) * -1;
					} else if (j == 9){
						revealedBoard[i][j] = (board[i + 1][j] + board[i][j - 1] + board[i + 1][j - 1]) * -1;
					} else{
						revealedBoard[i][j] = (board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1]) * -1;
					}
				} else if (i == 9){
					if(j == 0){
						revealedBoard[i][j] = (board[i - 1][j] + board[i - 1][j + 1] + board[i][j + 1]) * -1;
					} else if (j == 9){
						revealedBoard[i][j] = (board[i][j - 1] + board[i - 1][j - 1] + board[i - 1][j]) * -1;
					} else{
						revealedBoard[i][j] = (board[i - 1][j - 1] + board[i - 1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j - 1]) * -1;
					}
				} else if (j == 0)
					revealedBoard[i][j] = (board[i - 1][j] + board[i - 1][j + 1] + board[i + 1][j + 1] + board[i + 1][j] + board[i + 1][j + 1]) * -1;
				 else if (j == 9)
					revealedBoard[i][j] = (board[i - 1][j - 1] + board[i - 1][j] + board[i][j - 1] + board[i + 1][j - 1] + board[i + 1][j]) * -1;
				 else
					revealedBoard[i][j] = (board[i - 1][j - 1] + board[i -1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1]) * -1;
			} else {
				revealedBoard[i][j] = -1;
			}
			printf("%d ", revealedBoard[i][j]);
		}
		printf("\n");
	}
}

void printBoard() {
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            if (revealed[i][j]) {
                if (board[i][j] == -1) {
                    printf("* ");
                } else {
                    printf("%d ", revealedBoard[i][j]);
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main() {
    int x, y;

    initializeBoard();
    printf("Welcome to Minesweeper!\n");

    while (1) {
        printBoard();
        printf("Enter coordinates (x y): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }

        if (revealed[x][y]) {
            printf("Already revealed. Try again.\n");
            continue;
        }

        revealed[x][y] = 1;

        if (board[x][y] == -1) {
            printf("Game Over! You hit a mine.\n");
            break;
        }
    }

    return 0;
}
