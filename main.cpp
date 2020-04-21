#include "teacodec.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<StatusLevel>("StatusLevel");

    QApplication a(argc, argv);
    TeaCodec w;
    w.show();
    return a.exec();
}
