#include "musicapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    musicapp w;
    w.show();
    return a.exec();
}
