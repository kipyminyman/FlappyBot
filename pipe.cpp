#include "pipe.h"

int Pipe::width = 3*26;
int Pipe::gap_size = 140;
int Pipe::bottomGap = 56 * 3;
int Pipe::max_height = 135 * 3; //256 * 3 - Pipe::bottomGap - Pipe::gap_size;
int Pipe::min_height = 256*3 - bottomGap - (121*3 + gap_size);

//x + g + l + gr = h

Pipe::Pipe(int x, int h, int s)
{
    if (h == -1) { h = rand() % (max_height - min_height) + min_height; }
    height = h;
    this->x = x;
    speed = s;
}
void Pipe::step()
{
    x += speed;
}

sf::RectangleShape Pipe::getUpperPipe()
{
    sf::RectangleShape ret = sf::RectangleShape(sf::Vector2f(width, max_height - height + bottomGap));
    ret.setPosition(x, height + gap_size);
    return ret;
}
sf::RectangleShape Pipe::getLowerPipe()
{
    sf::RectangleShape ret = sf::RectangleShape(sf::Vector2f(width, height));
    ret.setPosition(x, 0);
    return ret;
}

int Pipe::getx()
{
    return x;
}
int Pipe::getFrontX()
{
    return x;
}
int Pipe::getBackX()
{
    return x + width;
}
void Pipe::reset()
{
    height = rand() % (max_height - min_height) + min_height;
}

void Pipe::setSpeed(int s)
{
    speed = s;
}
