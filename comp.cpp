#include "comp.h"

double Computer::mut_rate = .01;

void Computer::pass(double h, double d)
{
    h_node = h;
    d_node = d;
}
void Computer::step()
{
    state = h_node * h_connection + d_node * d_connection + bias;
}
void Computer::mutate()
{
    h_connection += (double(rand())/double(RAND_MAX) - .5) * mut_rate;
    d_connection += (double(rand())/double(RAND_MAX) - .5) * mut_rate;
    bias += (double(rand())/double(RAND_MAX) - .5) * mut_rate;
}

bool Computer::doJump()
{
    return state >= 0;
}
