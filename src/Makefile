CXX=g++ -Wall -Werror -c
LD=g++

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
Main.exe: $(OBJ)
	$(LD) $(OBJ) -o $@
	
%.o: %.cpp
	$(CXX) $< -o $@


FIFO.o: FIFO.cpp Knapsack.h
Knapsack.o: Knapsack.cpp Knapsack.h
Heap.o: Heap.cpp Heap.h
LC.o: LC.cpp Heap.h Knapsack.h
main.o: main.cpp Knapsack.h
greedymethod.o: greedymethod.cpp Knapsack.h
Backtrack.o: Backtrack.cpp Knapsack.h
dp.o: dp.cpp Knapsack.h

run: Main.exe
	.\Main.exe

.PHONY:clean run
clean:
	del *.o