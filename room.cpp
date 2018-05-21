#include "room.h"

Room::Room(int w, int h)
{
    c_pipe = 0;

    width = w;
    height = h;

    if (p.size() != 3) {
        p.push_back(Pipe(w));
        p.push_back(Pipe(w + w/2));
        p.push_back(Pipe(2 * w));
    }

    f_score.loadFromFile("Sprites/arial.ttf");
    // Create a text
    score = sf::Text("Null", f_score);
    score.setCharacterSize(30);
    score.setStyle(sf::Text::Bold);
    //score.setFillColor(sf::Color::White);
    score.setPosition(0,0);
    id = sf::Text("Null", f_score);
    id.setCharacterSize(30);
    id.setStyle(sf::Text::Bold);
    //score.setFillColor(sf::Color::White);
    id.setPosition(0, h - 30);

    sf::Image image;

    image.loadFromFile("Sprites/SPRITES.png");

    upper_tex.loadFromImage(image, sf::IntRect(302, 0, 26, 135));
    upper_tex.setRepeated(true);
    upper_pipe = sf::Sprite(upper_tex);
    upper_pipe.setScale(3, 3);

    lower_tex.loadFromImage(image, sf::IntRect(330, 0, 26, 121));
    lower_tex.setRepeated(true);
    lower_pipe = sf::Sprite(lower_tex);
    lower_pipe.setScale(3, 3);

    c_frame = 0;
    t_bird.resize(4);
    t_bird[0].loadFromImage(image, sf::IntRect(264, 64, 17, 12));
    t_bird[1].loadFromImage(image, sf::IntRect(264, 90, 17, 12));
    t_bird[2].loadFromImage(image, sf::IntRect(223, 124, 17, 12));
    t_bird[3].loadFromImage(image, sf::IntRect(264, 90, 17, 12));
    s_bird = sf::Sprite(t_bird[c_frame]);
    s_bird.setOrigin(9, 6);
    s_bird.setScale(3, 3);

    t_ground.loadFromImage(image, sf::IntRect(146, 0, 154, 56));
    s_ground = sf::Sprite(t_ground);
    s_ground.setScale(3, 3);
    s_ground.setPosition(0, height - 56 * 3);

    t_back.loadFromImage(image, sf::IntRect(0,0,144,256));
    s_back = sf::Sprite(t_back);
    s_back.setScale(3, 3);
}

void Room::draw(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { window.close(); }
    }


    c_frame += 1;
    c_frame %= 16;
    s_bird.setTexture(t_bird[c_frame/4]);
    s_bird.setPosition(b->getx(), height - b->gety());
    s_bird.setRotation(-atan2(b->getyVel(), 10) * 180.0 / 3.14159265);

    window.clear();
    window.draw(s_back);
    window.draw(s_bird);
    for (unsigned i = 0; i < p.size(); i++) {
        upper_pipe.setPosition(p[i].getx(), p[i].getUpperHeight() - 135 * 3);
        lower_pipe.setPosition(p[i].getx(), p[i].getLowerHeight());
        window.draw(upper_pipe);
        window.draw(lower_pipe);
    }

    window.draw(s_ground);
    window.draw(score);
    window.draw(id);
    window.display();
}
void Room::step()
{
    // stepping
    if (b->gety() > height) { b->sety(height); }
    b->step();

    for (unsigned i = 0; i < p.size(); i++) {
        if (p[i].getBackX() < 0) { p[i] = Pipe(width + width/2 + p[i].getx()); }
        p[i].step();
    }

    if (p[c_pipe].getBackX() < b->getx() - 9 * 3) { // Minus 8 for the centered offset of s_bird (+9, +6)
        c_pipe += 1;
        c_pipe %= 3;
        b->addPoint();
    }

    s_ground.move(-2, 0);
    if(s_ground.getPosition().x <= -7 * 3) { s_ground.move(7 * 3, 0); }

    score.setString(std::to_string(b->getScore()));

    // Collision checking
    s_bird.setPosition(b->getx(), height - b->gety());
    s_bird.setRotation(0);//atan2(b->getyVel(), 2) * 180.0 / 3.14159265);
    auto bounds = s_bird.getGlobalBounds();
    for (unsigned i = 0; i < p.size(); i++) {
        if (bounds.intersects(p[i].getUpperPipe().getGlobalBounds()) ||
            bounds.intersects(p[i].getLowerPipe().getGlobalBounds())) {
            b->kill();
            return;
        }
    }
    if (bounds.intersects(s_ground.getGlobalBounds())) {
        b->kill();
    }
}
void Room::reset()
{
    c_pipe = 0;

    if (p.size() == 3) {
        p[0].setx(width);
        p[0].reset();
        p[1].setx(width + width / 2);
        p[1].reset();
        p[2].setx(width * 2);
        p[2].reset();
    }
}

void Room::setBird(Bird* b)
{
    this->b = b;
    id.setString(std::to_string(this->b->getID()));
}
