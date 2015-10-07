
#include "zhuma.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ZhuMa zhuma;
    zhuma.show();

    return a.exec();
}
