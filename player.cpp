#include "player.h"

void Player::step()
{

}
bool Player::doJump()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_hold) {
        is_hold = true;
        return true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        is_hold = false;
    }
    return false;
}
