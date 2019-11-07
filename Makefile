all:pushboxgame

pushboxgame:game.o map.o main.o score.o
	g++ -W -Wall -g -o pushboxgame score.o game.o map.o main.o -lncurses

Score.o:score.cpp
	g++ -W -Wall -g -c -o score.o score.cpp

game.o:game.cpp
	g++ -W -Wall -g -c -o game.o game.cpp 

map.o:map.cpp
	g++ -W -Wall -g -c -o map.o map.cpp

main.o:main.cpp
	g++ -W -Wall -g -c -o main.o main.cpp

clean:
	rm pushboxgame ./*.o
