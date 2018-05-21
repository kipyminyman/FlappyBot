main:
	g++ controller.cpp comp.cpp player.cpp pipe.cpp bird.cpp room.cpp main.cpp -std=c++0x -o flap -lsfml-system -lsfml-graphics -lsfml-window -lstdc++

clean :
	rm flap *.o
