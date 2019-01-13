#include <QCoreApplication>

#include "treeofshape.h"
#include "colortreeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //TreeOfShape tree = TreeOfShape("/home/nathan/Documents/TIGD/test2.pgm");
    TreeOfShape tree = TreeOfShape("../test2.pgm");

    //tree.saveGraphe("/home/nathan/Documents/TIGD/result.gv");
    tree.saveGraphe("../result.gv");


    tree.removeShape(4);

    colorTreeOfShape c_tree("../test_color.ppm");


    return a.exec();
}
