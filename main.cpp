#include "reaktride.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    reaktrIDE w;
    w.showMaximized();
    w.show();
    return a.exec();
}
