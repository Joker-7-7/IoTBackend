#include "IoT.h"
#include "Radio2.h"

IoT::IoT() :
    running_(false)
{
}

Token IoT::Sensor::read()
{
    return input;
}

void IoT::Actuator::write(Token token)
{
    output = token;
    qDebug() << "Token written to Actuator";
}

IoT::~IoT()
{
    stopProcessing();
}

void IoT::sync()
{
    qDebug() << "Button pressed: Starting communication via RADIO-1";
    if(r1 != nullptr)
    {
        r1->connect();
        auto tokens = r1->exchange(geo);
        for (auto& token : tokens) {
            qDebug() << "Token exchanged via RADIO-1";
        }
        r1->disconnect();
    }
}

void IoT::setRadio1(std::shared_ptr<AbstractRadio1> radio1) {
    r1 = radio1;
}

void IoT::setRadio2(std::shared_ptr<AbstractRadio2> radio2) {
    r2 = radio2;
}

void IoT::propagate()
{
    qDebug() << "Sensor data available: Propagating via RADIO-2";
    auto token = rx.read();
    if(r2 != nullptr)
    {
        r2->propagate(token);
    }
}

void IoT::process(Token token)
{
    qDebug() << "Processing data for Actuator";
    tx.write(token);
}

void IoT::enqueueTask(std::shared_ptr<Task> task)
{
    {
        QMutexLocker locker(&queueMutex_);
        taskQueue_.enqueue(task);
    }
    taskAdded_.wakeOne();
}

void IoT::startProcessing()
{
    if (running_.load()) return;
    running_.store(true);
    workerThread_ = std::thread(&IoT::processQueue, this);
}

void IoT::stopProcessing()
{
    {
        QMutexLocker locker(&queueMutex_);
        running_.store(false);
        taskAdded_.wakeAll();
    }
    if (workerThread_.joinable())
    {
        workerThread_.join();
    }
}

void IoT::processQueue()
{
    while (running_.load())
    {
       std::shared_ptr<Task> task;
        {
            QMutexLocker locker(&queueMutex_);
            if (taskQueue_.isEmpty())
            {
                taskAdded_.wait(&queueMutex_);
                if (!running_.load()) return;
            }

            if (!taskQueue_.isEmpty())
            {
                task = taskQueue_.dequeue();
            }
        }

        if (task)
        {
            task->execute();
        }
    }
}
