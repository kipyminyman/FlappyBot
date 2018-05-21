#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller
{
public:
    Controller() {}
    virtual void step() {}
    virtual bool doJump() {}
};

#endif
