#target: reqs
#	build inst.
#	build with g++ version 9.3.0
program: main.o AStar.o state.o 
	g++ -o program main.o AStar.o state.o

main.o: main.cpp
	g++ -c main.cpp

AStar.o: AStar.cpp AStar.h
	g++ -c AStar.cpp

state.o: state.cpp state.h
	g++ -c state.cpp

clean:
	rm -f program main.o AStar.o state.o 