#include "pattern.h"
#include "spinslider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pattern w;
    // SpinSlider w;
    w.show();

    return a.exec();
}
