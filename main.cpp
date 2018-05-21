#include "room.h"
#include "player.h"
#include "comp.h"

int main()
{
    srand(time(NULL));

    int width = 144 * 3;
    int height = 256 * 3;

    sf::RenderWindow window(sf::VideoMode(width, height), "Bappy Flird");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Computer p = Computer();
    Bird b = Bird(&p, width/2, height/2);
    Room r = Room(width, height);
    r.setBird(&b);
    bool do_draw = true;

    std::vector<std::pair<Computer, int>> gene_pool;
    std::vector<Computer> population;

    int constSize = 2000;

    for (unsigned i = 0; i < constSize; i++) {
        population.push_back(Computer());
    }

    int counter = 0;

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {}

    while (window.isOpen()) {

        double average = 0;

        // Fit population
        gene_pool.resize(0);
        std::cout << "Fitting population (generation " << counter << ")" << std::endl;
        for (unsigned i = 0; i < population.size(); i++) {

            b = Bird(&population[i], width/2, height/2);
            b.setID(i);
            r.reset();
            r.setBird(&b);

            while (!b.isDead()) {
                population[i].pass(double(b.gety())/double(800), r.getd());
                population[i].step();
                r.step();

                //if (b.getScore() > 0 && do_draw) { r.draw(window); }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { do_draw = true; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { do_draw = false; }//*/
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { population[i].print(); }
                if (do_draw) { r.draw(window); }
            }

            average += b.getScore();

            if (b.getScore() > 0) { gene_pool.push_back(std::pair<Computer, int>(population[i], b.getScore())); }
        }

        average /= double(constSize);

        // Generate next population
        std::cout << "Average distance: " << average << std::endl;
        std::cout << "Generating next population." << std::endl;
        if (gene_pool.size() == 0) { gene_pool.push_back(std::pair<Computer, int>(population[rand()%constSize], 0)); }
        population.resize(0);
        for (unsigned i = 0; i < constSize; i++) {
            int ind1 = rand() % gene_pool.size();
            int ind2 = rand() % gene_pool.size();

            if (gene_pool[ind1].second > gene_pool[ind2].second) { population.push_back(gene_pool[ind1].first); }
            else { population.push_back(gene_pool[ind2].first); }

            population.back().mutate();
        }
        counter++;
    }

    return 0;
}
