#ifndef BIRD_H_
#define BIRD_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "controller.h"

class Bird
{
public:
    Bird(Controller* b, int initx, int inity);

    void jump();
    void step();
    void kill() { is_dead = true; }
    void addPoint() { score++; }

    int getx();
    int gety();
    double getxVel();
    double getyVel();

    int getAge() { return ticks_alive; }
    int getScore() { return score; }
    bool isDead() { return is_dead; }

    sf::RectangleShape getBody();

    void sety(int n) { y = n; }
    void setx(int n) { x = n; }

    void setID(int id) { this->id = id; }
    int getID() { return id; }

private:
    double x;
    double y;
    double x_vel;
    double y_vel;
    int ticks_alive;
    int score;
    bool is_dead;

    int id;

    Controller* brain;

    static double grav;
    static double jump_speed;
    static unsigned int body_size;
};

#endif
