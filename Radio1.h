#pragma once
#include "AbstractRadio1.h"

#include <QApplication>

class Radio1 : public AbstractRadio1
{
public:
    Radio1() = default;
    void disconnect() override;

    std::vector<Token> exchange(GEO geo) override;

    void connect() override;

    const int MAXNEIGHBORS = 10;

private:
    BackEndConnectionParam params_;
};
