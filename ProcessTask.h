#pragma once

#include "Task.h"
#include "MocObjects.h"

class IoT;

class ProcessTask : public Task
{
public:
    ProcessTask(IoT* iot, Token token);
    void execute() override;

private:
    IoT* iot_;
    Token token_;
};
