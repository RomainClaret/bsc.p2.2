#include <QApplication>
#include "convertisseur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Convertisseur w;
    w.show();

    return a.exec();
}
