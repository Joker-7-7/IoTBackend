#pragma once

#include "Task.h"

class IoT;

class SyncTask : public Task
{
public:
    SyncTask(IoT* iot);
    void execute() override;

private:
    IoT* iot_;
};
