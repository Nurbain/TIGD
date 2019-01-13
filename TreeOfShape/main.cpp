#include <QCoreApplication>

#include "treeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //TreeOfShape tree = TreeOfShape("/home/nathan/Documents/TIGD/test2.pgm");
    TreeOfShape tree = TreeOfShape("../test2.pgm");

    //tree.saveGraphe("/home/nathan/Documents/TIGD/result.gv");
    tree.saveGraphe("../result.gv");

    tree.removeShape(4);

    return a.exec();
}
