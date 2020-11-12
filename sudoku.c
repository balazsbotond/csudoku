#include <stdio.h>
#include <time.h>

typedef int Board[9][9];

Board easyBoard = {
    {3, 4, 0, 0, 2, 6, 0, 8, 0},
    {0, 0, 1, 0, 7, 0, 0, 0, 0},
    {7, 2, 0, 8, 0, 0, 4, 3, 9},
    {4, 0, 9, 6, 0, 0, 3, 0, 2},
    {0, 0, 0, 0, 1, 9, 0, 7, 0},
    {1, 0, 0, 0, 0, 4, 9, 0, 0},
    {0, 0, 0, 5, 6, 8, 0, 0, 7},
    {0, 0, 0, 0, 0, 2, 0, 0, 5},
    {2, 5, 4, 0, 9, 7, 8, 6, 3}
};

Board hardBoard = {
    {0, 6, 0, 0, 1, 0, 8, 7, 0},
    {0, 9, 0, 0, 8, 0, 6, 0, 0},
    {0, 0, 0, 6, 2, 0, 0, 0, 0},
    {0, 0, 0, 9, 6, 0, 0, 0, 0},
    {0, 0, 5, 0, 0, 0, 0, 0, 2},
    {0, 7, 9, 0, 0, 0, 0, 0, 5},
    {0, 0, 0, 0, 0, 4, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 8, 0},
    {8, 0, 0, 0, 0, 0, 0, 5, 1}
};

Board emptyBoard = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void printBoard(Board *board) {
    for (int row = 0; row < 9; row++) {
        printf("%d %d %d | %d %d %d | %d %d %d\n",
            (*board)[row][0], (*board)[row][1], (*board)[row][2],
            (*board)[row][3], (*board)[row][4], (*board)[row][5],
            (*board)[row][6], (*board)[row][7], (*board)[row][8]);
        if (row == 2 || row == 5) {
            printf("------+-------+------\n");
        }
    }
}

int isValid(int num, int row, int col, Board *board) {
    if ((*board)[row][col] != 0) {
        return 0;
    }
    for (int c = 0; c < 9; c++) {
        if ((*board)[row][c] == num) {
            return 0;
        }
    }
    for (int r = 0; r < 9; r++) {
        if ((*board)[r][col] == num) {
            return 0;
        }
    }
    int boxLeft = col / 3 * 3;
    int boxTop = row / 3 * 3;
    for (int r = boxTop; r < boxTop + 3; r++) {
        for (int c = boxLeft; c < boxLeft + 3; c++) {
            if ((*board)[r][c] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int solve(Board *board, int row, int col) {
    if (row == 9) {
        return 1; // puzzle solved
    }
    int nextRow = col < 8 ? row : row + 1;
    int nextCol = col < 8 ? col + 1 : 0;
    if ((*board)[row][col] != 0) {
        return solve(board, nextRow, nextCol);
    }
    for (int i = 0; i <= 9; i++) {
        if (!isValid(i, row, col, board)) {
            continue;
        }
        (*board)[row][col] = i;
        if (solve(board, nextRow, nextCol)) {
            return 1;
        }
        (*board)[row][col] = 0;
    }
    return 0; // dead end
}

int main() {
    Board *board = &hardBoard;

    time_t start = clock();
    int success = solve(board, 0, 0);
    time_t elapsed = clock() - start;
    double elapsedMs = ((double)elapsed) / CLOCKS_PER_SEC * 1000;

    if (success) {
        printBoard(board);
        printf("\nSolution found.\n");
    } else {
        printf("Unsolvable puzzle.\n");
    }
    printf("Elapsed time: %f ms.\n", elapsedMs);

    return 0;
}
