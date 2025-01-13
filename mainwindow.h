#pragma once
#include "Radio1.h"
#include "Radio2.h"
#include "IoT.h"

#include <QMainWindow>
#include <QStateMachine>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStateMachine>
#include <QState>
#include <QFinalState>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private:
    void SetupStates() noexcept;
    void SetupTransitions() noexcept;
    void TestIoT() noexcept;

    Ui::MainWindow* ui;

    // UI Components
    QLabel* label_;
    QPushButton* buttonA_;
    QPushButton* buttonB_;
    QPushButton* buttonC_;
    QPushButton* exitButton_;

    // State machine
    QStateMachine machine_;
    QState* stateA_;
    QState* stateB_;
    QState* stateC_;
    QFinalState* finalState_;

    // IoT Components
    IoT iot_;
    std::shared_ptr<Radio1> radio1_;
    std::shared_ptr<Radio2> radio2_;
};
