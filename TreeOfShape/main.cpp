#include <QCoreApplication>

#include "treeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    TreeOfShape tree = TreeOfShape("../testInterp.pgm");

    tree.image.print();

    tree.saveGraphe("../result.gv");


    return a.exec();
}
