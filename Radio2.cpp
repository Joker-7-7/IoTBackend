#include "Radio2.h"
#include "IoT.h"

void Radio2::propagate(Token token)
{
    qDebug() << "Radio2: Propagating data";
}

void Radio2::process(Token token)
{
    qDebug() << "Radio2: Processing data";
    iot->process(token);
}
