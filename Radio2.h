#pragma once
#include "AbstractRadio2.h"

#include <QApplication>

class IoT;

class Radio2 : public AbstractRadio2
{
public:
    Radio2() = default;
    void propagate(Token token) override;
    void process(Token token) override;

signals:
    void RadioPacketSignal();

public:
    IoT* iot = nullptr;
};
