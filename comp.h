#ifndef COMP_H_
#define COMP_H_

#include "controller.h"
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>

class Computer : public Controller
{
public:
    Computer() {
        h_connection = double(rand())/double(RAND_MAX) - .5;
        d_connection = double(rand())/double(RAND_MAX) - .5;
        bias = double(rand())/double(RAND_MAX) - .5;
    }
    Computer(double h_, double d_, double b_) { h_connection = h_; d_connection = d_; bias = b_; }
    void pass(double h, double d);
    void step();
    bool doJump();

    void mutate();

    void print() { std::cout << "H_CON: " << h_connection << std::endl << "D_CON: " << d_connection << std::endl << "BIAS: " << bias << std::endl; }
private:
    double h_connection;
    double d_connection;
    double bias;
    double h_node;
    double d_node;

    double state;

    static double mut_rate;
};

#endif
