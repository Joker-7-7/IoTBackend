#pragma once
#include "MocObjects.h"
#include "AbstractRadio1.h"
#include "AbstractRadio2.h"
#include "Task.h"

#include <QApplication>
#include <QQueue>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class Radio2;

class IoT
{
public:
    class Sensor
    {
    public:
        Token read();
    private:
        Token input;
        IoT* iot;
    };

    class Actuator
    {
    public:
        void write(Token token);
    private:
        Token output;
    };

    IoT();
    ~IoT();

    void propagate();

    void process(Token token);

    void setRadio1(std::shared_ptr<AbstractRadio1> radio1);
    void setRadio2(std::shared_ptr<AbstractRadio2> radio2);

    void enqueueTask(std::shared_ptr<Task> task);
    void startProcessing();
    void stopProcessing();

    std::shared_ptr<AbstractRadio1> r1;
    std::shared_ptr<AbstractRadio2> r2;

public slots:
    void sync();

private:
    void processQueue();

    GEO geo;
    Sensor rx;
    Actuator tx;

    QQueue<std::shared_ptr<Task>> taskQueue_;
    QMutex queueMutex_;
    QWaitCondition taskAdded_;
    std::thread workerThread_;
    std::atomic<bool> running_;
};





