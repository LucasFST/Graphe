CXX_COMPILER=g++
CXX_FLAGS=-Wall -Wextra -Wfatal-errors -std=c++11

.PHONY=all clean

all: graphe.o main.o exe 

graphe.o : src/graphe.h src/graphe.cpp
	$(CXX_COMPILER) -c src/graphe.cpp -o $@ $(CXX_FLAGS)

main.o: src/main.cpp src/graphe.h
	$(CXX_COMPILER) -c src/main.cpp -o $@ $(CXX_FLAGS)

exe: main.o graphe.o
	$(CXX_COMPILER) main.o graphe.o -o $@ $(CXX_FLAGS)