CC = g++
CPPFLAGS = --std=c++11

queen: bitwise_solver.o dlx_solver.o queen_main.o ../dance/dance.o ../dance/exact_cover_puzzle_maker.o
	$(CC) $(CPPFLAGS) bitwise_solver.o dlx_solver.o queen_main.o ../dance/dance.o ../dance/exact_cover_puzzle_maker.o -o queen

clean:
	rm *.o *.exe queen
