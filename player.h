#ifndef PLAYER_H_
#define PLAYER_H_

#include "controller.h"
#include <SFML/Graphics.hpp>

class Player : public Controller
{
public:
    Player() { is_hold = false; }
    void step();
    bool doJump();

private:
    bool is_hold;
};

#endif
