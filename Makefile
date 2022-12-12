CXX_COMPILER=g++
CXX_FLAGS=-Wall -Wextra -Wfatal-errors -std=c++11

.PHONY=all clean

all: obj/graphe.o obj/main.o bin/exe 

obj/graphe.o : src/graphe.h src/graphe.cpp
	$(CXX_COMPILER) -c src/graphe.cpp -o $@ $(CXX_FLAGS)

obj/main.o: src/main.cpp src/graphe.h
	$(CXX_COMPILER) -c src/main.cpp -o $@ $(CXX_FLAGS)

bin/exe: obj/main.o obj/graphe.o
	$(CXX_COMPILER) obj/main.o obj/graphe.o -o $@ $(CXX_FLAGS)

clean :
	rm -f obj/*
	rm -f bin/*