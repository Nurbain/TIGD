#include <QCoreApplication>

#include "treeofshape.h"
#include "colortreeofshape.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //TreeOfShape tree = TreeOfShape("/home/nathan/Documents/TIGD/test2.pgm");
    TreeOfShape tree = TreeOfShape("../petite_bombe_atomique.pgm");

    //tree.saveGraphe("/home/nathan/Documents/TIGD/result.gv");
    tree.saveGraphe("../result.gv");


    tree.removeShape(20000);

    //colorTreeOfShape c_tree("../Lena.ppm");


    return a.exec();
}
