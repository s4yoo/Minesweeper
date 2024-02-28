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
	 	    revealedBoard[i][j] = 0;
        }
    }

    // 랜덤하게 지뢰 배치
    srand(time(NULL));
    for (int i = 0; i < MINES; i++) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        board[x][y] = -1;
    }

	// 지뢰 힌트 보드 만들기
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != -1) {
				int sum = 0;
				int count = 0;

				for (int x = i - 1; x <= i + 1; x++) {
					for (int y = j - 1; y <= j + 1; y++) {
						if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
							sum += board[x][y];
							count++;
						}
					}
				}

				revealedBoard[i][j] = sum * -1;
			} else {
				revealedBoard[i][j] = -1;
			}
		}
	}

	// for(int i = 0; i < SIZE; i++){
	// 	for(int j = 0; j < SIZE; j++){
	// 		if(board[i][j] != -1){
	// 			if(i == 0){
	// 				if(j == 0)
	// 					revealedBoard[i][j] = (board[i + 1][j] + board[i][j + 1] + board[i + 1][j + 1]) * -1;
	// 				else if (j == 9)
	// 					revealedBoard[i][j] = (board[i + 1][j] + board[i][j - 1] + board[i + 1][j - 1]) * -1;
	// 				else
	// 					revealedBoard[i][j] = (board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1]) * -1;
	// 			} else if (i == 9){
	// 				if(j == 0)
	// 					revealedBoard[i][j] = (board[i - 1][j] + board[i - 1][j + 1] + board[i][j + 1]) * -1;
	// 				else if (j == 9)
	// 					revealedBoard[i][j] = (board[i][j - 1] + board[i - 1][j - 1] + board[i - 1][j]) * -1;
	// 				else
	// 					revealedBoard[i][j] = (board[i - 1][j - 1] + board[i - 1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j + 1]) * -1;
	// 			} else if (j == 0)
	// 				revealedBoard[i][j] = (board[i - 1][j] + board[i - 1][j + 1] + board[i + 1][j + 1] + board[i + 1][j] + board[i + 1][j + 1]) * -1;
	// 			else if (j == 9)
	// 				revealedBoard[i][j] = (board[i - 1][j - 1] + board[i - 1][j] + board[i][j - 1] + board[i + 1][j - 1] + board[i + 1][j]) * -1;
	// 			else
	// 				revealedBoard[i][j] = (board[i - 1][j - 1] + board[i -1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1]) * -1;
	// 		} else
	// 			revealedBoard[i][j] = -1;
	// 	}
	// }
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

void verifyBoard(int x, int y) {
    if (revealed[x][y] != 0) {
        return; // 이미 확인한 셀이라면 종료
    }

    revealed[x][y] = 1; // 현재 셀을 확인했다고 표시

    if (revealedBoard[x][y] == 0) {
        // 주변 셀을 확인하기 위한 상대적인 위치 배열
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 보드의 경계를 벗어나는지 확인
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                // 인접한 셀이 0이면 재귀적으로 확인
                if (revealedBoard[nx][ny] == 0) {
                    verifyBoard(nx, ny);
                } else if (revealedBoard[nx][ny] != -1) {
                    // 인접한 셀이 -1이 아니라면 확인 완료
                    revealed[nx][ny] = 1;
                }
            }
        }
    }
}

// void verifyBoard(int x, int y){
// 	if (revealed[x][y] != 1) {
// 		revealed[x][y] = 1;
	
// 		if(revealedBoard[x][y] == 0) {
// 			if (x - 1 >= 0)
// 				if(revealedBoard[x - 1][y] == 0)
// 					verifyBoard(x - 1, y);
// 				else if (revealedBoard[x - 1][y] != -1)
// 					revealed[x - 1][y] = 1;

// 			if (x + 1 <= 9)
// 				if(revealedBoard[x + 1][y] == 0)
// 					verifyBoard(x + 1, y);
// 				else if (revealedBoard[x + 1][y] != -1)
// 					revealed[x + 1][y] = 1;

// 			if (y - 1 >= 0)
// 				if(revealedBoard[x][y - 1] == 0)
// 					verifyBoard(x, y - 1);
// 				else if (revealedBoard[x][y - 1] != -1)
// 					revealed[x][y - 1] = 1;

// 			if (y + 1 <= 9)
// 				if(revealedBoard[x][y + 1] == 0)
// 					verifyBoard(x, y + 1);
// 				else if (revealedBoard[x][y + 1] != -1)
// 					revealed[x][y + 1] = 1;
// 		}
// 	}
// 	return;
// }

int main() {
    int x, y;
	char inputKey;
    printf("Welcome to Minesweeper!\n");

	while (1) {
        initializeBoard();

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

            // revealed[x][y] = 1;
            verifyBoard(x, y);

            if (board[x][y] == -1) {
                printf("Game Over! You hit a mine.\n");
                break;
            }
        }

        while (1) {
            printf("Continue?(Y/N) : ");
            scanf(" %c", &inputKey);

            if (inputKey == 'Y' || inputKey == 'y' || inputKey == 'N' || inputKey == 'n') {
                break;
            } else {
                printf("Invalid input. Please enter Y or N.\n");
            }
        }

        if (inputKey == 'N' || inputKey == 'n') {
            return 0;
        }
    }

    return 0;
}
