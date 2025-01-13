#include "mainwindow.h"
#include "SyncTask.h"
#include "PropagateTask.h"
#include "ProcessTask.h"

#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

#include <memory>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    label_(new QLabel("Current State: None", this)),
    buttonA_(new QPushButton("Go to State A", this)),
    buttonB_(new QPushButton("Go to State B", this)),
    buttonC_(new QPushButton("Go to State C", this)),
    exitButton_(new QPushButton("Exit", this)),
    stateA_(new QState()),
    stateB_(new QState()),
    stateC_(new QState()),
    finalState_(new QFinalState())
{
    // Set up IoT components
    radio1_ = std::make_shared<Radio1>();
    radio2_ = std::make_shared<Radio2>();
    iot_.setRadio1(radio1_);
    iot_.setRadio2(radio2_);
    radio2_->iot = &iot_;


    iot_.startProcessing();

    // Layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(label_);
    layout->addWidget(buttonA_);
    layout->addWidget(buttonB_);
    layout->addWidget(buttonC_);
    layout->addWidget(exitButton_);
    setCentralWidget(centralWidget);

    // Setup states and transitions
    SetupStates();
    SetupTransitions();

    // Start the state machine
    machine_.setInitialState(stateB_);
    machine_.start();

    TestIoT();
}

void MainWindow::SetupStates() noexcept
{
    QObject::connect(stateA_, &QState::entered, [&]() {
        label_->setText("Current State: A");
        iot_.enqueueTask(std::make_shared<SyncTask>(&iot_));
    });

    QObject::connect(stateB_, &QState::entered, [&]() {
        label_->setText("Current State: B");
        iot_.enqueueTask(std::make_shared<PropagateTask>(&iot_));
    });

    QObject::connect(stateC_, &QState::entered, [&]() {
        label_->setText("Current State: C");
        iot_.enqueueTask(std::make_shared<ProcessTask>(&iot_, Token{}));
    });

    // Add states to the machine
    machine_.addState(stateA_);
    machine_.addState(stateB_);
    machine_.addState(stateC_);
    machine_.addState(finalState_);
}

void MainWindow::SetupTransitions() noexcept
{
    // Transitions from State A
    stateA_->addTransition(buttonB_, &QPushButton::clicked, stateB_);
    stateA_->addTransition(buttonC_, &QPushButton::clicked, stateC_);
    stateA_->addTransition(exitButton_, &QPushButton::clicked, finalState_);

    // Transitions from State B
    stateB_->addTransition(buttonA_, &QPushButton::clicked, stateA_);
    stateB_->addTransition(buttonC_, &QPushButton::clicked, stateC_);
    stateB_->addTransition(exitButton_, &QPushButton::clicked, finalState_);

    // Transitions from State C
    stateC_->addTransition(buttonA_, &QPushButton::clicked, stateA_);
    stateC_->addTransition(buttonB_, &QPushButton::clicked, stateB_);
    stateC_->addTransition(exitButton_, &QPushButton::clicked, finalState_);

    // Close application when reaching the final state
    QObject::connect(&machine_, &QStateMachine::finished, qApp, &QApplication::quit);
}

void MainWindow::TestIoT() noexcept
{
    // Parallel events in IoT
    std::thread threadA([this]() {
        QMetaObject::invokeMethod(buttonA_, "click", Qt::QueuedConnection);
    });

    std::thread threadB([this]() {
        QMetaObject::invokeMethod(buttonB_, "click", Qt::QueuedConnection);
    });

    std::thread threadC([this]() {
        QMetaObject::invokeMethod(buttonC_, "click", Qt::QueuedConnection);
    });

    threadA.detach();
    threadB.detach();
    threadC.detach();
}
