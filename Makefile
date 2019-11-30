all:pushboxgame

pushboxgame:game.o map.o main.o score.o user.o solver.o game.o
	g++ -std=c++11 -W -Wall -g -o pushboxgame score.o game.o map.o user.o solver.o main.o -lncurses 

Score.o:score.cpp
	g++ -std=c++11 -W -Wall -g -c -o score.o score.cpp 

game.o:game.cpp
	g++ -std=c++11 -W -Wall -g -c -o game.o game.cpp 

map.o:map.cpp
	g++ -std=c++11 -W -Wall -g -c -o map.o map.cpp 

user.o:user.cpp
	g++ -std=c++11 -W -Wall -g -c -o user.o user.cpp 

solver.o:solver.cpp
	g++ -std=c++11 -W -Wall -g -c -o solver.o solver.cpp 

main.o:main.cpp
	g++ -std=c++11 -W -Wall -g -c -o main.o main.cpp 

clean:
	rm pushboxgame ./*.o
