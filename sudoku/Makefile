all: solve transform

solve: sudokuSolve.o solve.o
	g++ -o solve sudokuSolve.o solve.o
sudokuSolve.o: sudokuSolve.cpp sudoku.h
	g++ -c sudokuSolve.cpp
solve.o: solve.cpp sudoku.h
	g++ -c solve.cpp

transform: transform.o
	g++ -o transform transform.o

transform.o: transform.cpp
	g++ -c transform.cpp




clean:
	rm solve transform *.o

