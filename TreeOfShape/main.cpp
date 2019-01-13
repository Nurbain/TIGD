#include <QCoreApplication>

#include "treeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    TreeOfShape tree = TreeOfShape("../test2.pgm");

    tree.saveGraphe("../result.gv");


    return a.exec();
}
