#ifndef PIPE_H_
#define PIPE_H_

#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class Pipe
{
public:
    Pipe(int x = 0, int h = -1, int s = -2);
    void step();
    int getFrontX();
    int getBackX();
    int getx();
    int getUpperHeight() { return height; }
    int getLowerHeight() { return height + gap_size; }
    int setx(int x) { this->x = x; }

    sf::RectangleShape getUpperPipe();
    sf::RectangleShape getLowerPipe();

    void reset();
    void setSpeed(int s);

private:
    static int width;
    static int gap_size;
    static int max_height;
    static int bottomGap;
    static int min_height;

    int speed;
    int height;
    int x;
};

#endif
