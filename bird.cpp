#include "bird.h"

double Bird::grav = -.7;
double Bird::jump_speed = 8;
unsigned int Bird::body_size = 30;

Bird::Bird(Controller* b, int initx, int inity)
{
    x = initx;
    y = inity;
    x_vel = 0;
    y_vel = 0;

    is_dead = false;
    score = 0;

    brain = b;
}

void Bird::step()
{
    y_vel += grav;
    y += y_vel;
    if (!is_dead) { ticks_alive++; }
    if (brain->doJump()) { jump(); }
}

sf::RectangleShape Bird::getBody()
{
    sf::RectangleShape ret = sf::RectangleShape(sf::Vector2f(body_size, body_size));
    ret.setPosition(sf::Vector2f(x,y));
    return ret;
}

void Bird::jump() { y_vel = jump_speed; }
int Bird::getx() { return x; }
int Bird::gety() { return y; }
double Bird::getxVel() { return x_vel; }
double Bird::getyVel() { return y_vel; }
