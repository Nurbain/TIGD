#include <QCoreApplication>

#include "treeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    TreeOfShape tree = TreeOfShape("../bombe_atomique.pgm");

    return a.exec();
}
