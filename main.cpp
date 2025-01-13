#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("State Machine Example");
    window.show();

    return app.exec();
}
