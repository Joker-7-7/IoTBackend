#pragma once

#include "Task.h"

class IoT;

class PropagateTask : public Task
{
public:
    PropagateTask(IoT* iot);
    void execute() override;

private:
    IoT* iot_;
};
