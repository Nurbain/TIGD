#include <QCoreApplication>

#include "treeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    TreeOfShape tree = TreeOfShape("../testInterp.pgm");
    tree.medianCalcule();
    tree.interpolate();

    tree.image.print();
    tree.interpolate_image_min.print();
    tree.interpolate_image_max.print();


    return a.exec();
}
