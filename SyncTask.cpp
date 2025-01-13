#include "SyncTask.h"
#include "Iot.h"

SyncTask::SyncTask(IoT* iot) :
    iot_(iot)
{
}

void SyncTask::execute()
{
    if (iot_) {
        iot_->sync();
    }
    qDebug() << "-----------------------";
}
