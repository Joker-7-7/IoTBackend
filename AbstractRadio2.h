#pragma once

#include "MocObjects.h"

class IoT;

class AbstractRadio2
{
public:
    virtual void propagate(Token token) = 0;
    virtual void process(Token token) = 0;
};
