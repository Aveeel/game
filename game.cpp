#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 4;
const int MAX_SCORE = 2048;

vector<vector<int>> board;
int score;

// Проверка на достижение цели
bool isGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return false;
            }
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
}

// Генерация новой миши
void addRandomTile() {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (board[row][col] != 0);
    board[row][col] = (rand() % 10) ? 2 : 4;
}

// Перемещение мишей
void moveTiles(int direction) {
    if (direction == 0) { // Влево
        for (int col = 0; col < SIZE; col++) {
            for (int row = 0; row < SIZE; row++) {
                if (board[row][col] != 0) {
                    int targetRow = row;
                    while (targetRow > 0 && board[targetRow - 1][col] == 0) {
                        targetRow--;
                    }
                    if (targetRow > 0 && board[targetRow - 1][col] == board[row][col]) {
                        board[targetRow - 1][col] *= 2;
                        board[row][col] = 0;
                        score += board[targetRow - 1][col];
                        row = targetRow;
                    }
                    while (targetRow > row) {
                        board[targetRow][col] = board[targetRow - 1][col];
                        board[targetRow - 1][col] = 0;
                        targetRow--;
                    }
                    board[targetRow][col] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    } else if (direction == 1) { // Вправо
        for (int col = SIZE - 1; col >= 0; col--) {
            for (int row = SIZE - 1; row >= 0; row--) {
                if (board[row][col] != 0) {
                    int targetRow = row;
                    while (targetRow < SIZE - 1 && board[targetRow + 1][col] == 0) {
                        targetRow++;
                    }
                    if (targetRow < SIZE - 1 && board[targetRow + 1][col] == board[row][col]) {
                        board[targetRow + 1][col] *= 2;
                        board[row][col] = 0;
                        score += board[targetRow + 1][col];
                        row = targetRow;
                    }
                    while (targetRow < row) {
                        board[targetRow][col] = board[targetRow + 1][col];
                        board[targetRow + 1][col] = 0;
                        targetRow++;
                    }
                    board[targetRow][col] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    } else if (direction == 2) { // Вверх
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (board[row][col] != 0) {
                    int targetCol = col;
                    while (targetCol > 0 && board[row][targetCol - 1] == 0) {
                        targetCol--;
                    }
                    if (targetCol > 0 && board[row][targetCol - 1] == board[row][col]) {
                        board[row][targetCol - 1] *= 2;
                        board[row][col] = 0;
                        score += board[row][targetCol - 1];
                        col = targetCol;
                    }
                    while (targetCol > col) {
                        board[row][targetCol] = board[row][targetCol - 1];
                        board[row][targetCol - 1] = 0;
                        targetCol--;
                    }
                    board[row][targetCol] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    } else if (direction == 3) { // Вниз
        for (int row = SIZE - 1; row >= 0; row--) {
            for (int col = SIZE - 1; col >= 0; col--) {
                if (board[row][col] != 0) {
                    int targetCol = col;
                    while (targetCol < SIZE - 1 && board[row][targetCol + 1] == 0) {
                        targetCol++;
                    }
                    if (targetCol < SIZE - 1 && board[row][targetCol + 1] == board[row][col]) {
                        board[row][targetCol + 1] *= 2;
                        board[row][col] = 0;
                        score += board[row][targetCol + 1];
                        col = targetCol;
                    }
                    while (targetCol < col) {
                        board[row][targetCol] = board[row][targetCol + 1];
                        board[row][targetCol + 1] = 0;
                        targetCol++;
                    }
                    board[row][targetCol] = board[row][col];
                    board[row][col] = 0;
                }
            }
        }
    }
}

// Вывод игрового поля
void printBoard() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    board.resize(SIZE, vector<int>(SIZE, 0));
    score = 0;

    // Игра
    while (true) {
        printBoard();
        cout << "Score: " << score << endl;

        int direction;
        cout << "Enter direction (0 - left, 1 - right, 2 - up, 3 - down): ";
        cin >> direction;

        moveTiles(direction);

        addRandomTile();

        if (isGameOver()) {
            cout << "Game over!" << endl;
            if (score == MAX_SCORE) {
                cout << "You win!" << endl;
            } else {
                cout << "You lose!" << endl;
            }
            break;
        }
    }

    return 0;
}
