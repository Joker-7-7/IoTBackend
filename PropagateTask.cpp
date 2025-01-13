#include "PropagateTask.h"
#include "IoT.h"

PropagateTask::PropagateTask(IoT* iot) :
    iot_(iot)
{
}

void PropagateTask::execute()
{
    if (iot_)
    {
        iot_->propagate();
    }
    qDebug() << "-----------------------";
}
