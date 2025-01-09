#include "qcardisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCarDisplay w;
    w.show();
    return a.exec();
}
