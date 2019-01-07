#include <QCoreApplication>

#include "treeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    TreeOfShape tree = TreeOfShape("/adhome/n/nu/nurbain/Documents/TIGD/TIGD/bombe_atomique.pgm");

    return a.exec();
}
