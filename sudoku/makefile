CC = g++
CPPFLAGS = --std=c++11

sudoku: search.o dlx.o sudoku_main.o ../dance/dance.o ../dance/exact_cover_puzzle_maker.o
	$(CC) $(CPPFLAGS) search.o dlx.o sudoku_main.o ../dance/dance.o ../dance/exact_cover_puzzle_maker.o -o sudoku

clean:
	rm *.o *.exe sudoku
