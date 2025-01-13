#include "ProcessTask.h"
#include "IoT.h"

ProcessTask::ProcessTask(IoT* iot, Token token) :
    iot_(iot),
    token_(token)
{
}

void ProcessTask::execute()
{
    if (iot_)
    {
        iot_->process(token_);
    }
    qDebug() << "-----------------------";
}
