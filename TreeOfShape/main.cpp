#include <QCoreApplication>

#include "treeofshape.h"
#include "colortreeofshape.h"

void test_im(const char *filename){
    std::clock_t start;
    double duration;

    start = std::clock();

    TreeOfShape tree = TreeOfShape(filename);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<< "temps compute tree "<< tree.image.width() << "*" << tree.image.height() << ": "<< duration  << std::endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test_im("../ImagesTests/Lena300x300.pgm");
    test_im("../ImagesTests/Lena400x400.pgm");
    test_im("../ImagesTests/Lena500x500.pgm");
    test_im("../ImagesTests/petite_bombe_atomique.pgm");

    //TreeOfShape tree = TreeOfShape("/home/nathan/Documents/TIGD/test2.pgm");
    TreeOfShape tree = TreeOfShape("../ImagesTests/test2.pgm");

    //tree.saveGraphe("/home/nathan/Documents/TIGD/result.gv");
    tree.saveGraphe("../result/result.gv");


    tree.removeShape(20000);

    colorTreeOfShape c_tree("../ImagesTests/JeuxTest.ppm");

    c_tree.treeMerge.saveGraphe("../result/result.gv");

    c_tree.removeShape(2000);


    return a.exec();
}
