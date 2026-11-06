#include "R34Clock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    R34Clock cl;
    cl.show();
    return QApplication::exec();
}
