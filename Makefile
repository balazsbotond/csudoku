all: sudoku

sudoku: sudoku.c
	$(CC) -o sudoku sudoku.c -Wall -W -pedantic -std=c99

clean:
	rm sudoku
