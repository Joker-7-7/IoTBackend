#include "Radio1.h"

void Radio1::disconnect()
{
    qDebug() << "Radio1: Disconnected";
}

std::vector<Token> Radio1::exchange(GEO geo)
{
    qDebug() << "Radio1: Exchanging data";
    return std::vector<Token>(MAXNEIGHBORS); // Генерация фиктивных данных
}

void Radio1::connect()
{
    qDebug() << "Radio1: Connected";
}
