#pragma once
#include "MocObjects.h"

#include <vector>

class AbstractRadio1
{
public:
    virtual void disconnect() = 0;

    virtual std::vector<Token> exchange(GEO geo) = 0;

    virtual void connect() = 0;
};
