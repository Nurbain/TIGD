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


    tree.removeShape(20000);

    /*colorTreeOfShape c_tree("../JeuxTest2.ppm");

    c_tree.treeMerge.saveGraphe("../result.gv");

    c_tree.removeShape(50);*/


    return a.exec();
}
