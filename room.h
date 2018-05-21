#ifndef ROOM_H_
#define ROOM_H_

#include "bird.h"
#include "pipe.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Room
{
public:
    Room(int w, int h);

    void draw(sf::RenderWindow& window);
    void step();
    void reset();

    void setBird(Bird* b);

    double getd() { return double(p[c_pipe].getLowerHeight())/double(height); }

private:
    Bird* b;
    std::vector<Pipe> p;
    int c_pipe;
    int c_frame;

    sf::Sprite upper_pipe;
    sf::Sprite lower_pipe;
    sf::Texture upper_tex;
    sf::Texture lower_tex;

    sf::Sprite s_bird;
    std::vector<sf::Texture> t_bird;

    sf::Sprite s_ground;
    sf::Texture t_ground;

    sf::Sprite s_back;
    sf::Texture t_back;

    sf::Text score;
    sf::Text id;
    sf::Font f_score;

    int width;
    int height;
};

#endif
