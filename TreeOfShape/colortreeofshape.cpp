#include "colortreeofshape.h"

colorTreeOfShape::colorTreeOfShape(const char *filename)
{
    if(LibTIM::Image<RGB>::load(filename,image)){
        std::cout << "Image Load" <<std::endl;
    }else{
        std::cout << "Image Non Load y'a un prb" <<std::endl;
        return;
    }

    imageR.setSize(image.getSizeX(),image.getSizeY(),1);
    for(int i=0;i<imageR.getSizeX();i++){
        for(int j=0;j<imageR.getSizeY();j++){
            imageR(i,j) = image(i,j)[0];
        }
    }
    imageG.setSize(image.getSizeX(),image.getSizeY(),1);
    for(int i=0;i<imageG.getSizeX();i++){
        for(int j=0;j<imageG.getSizeY();j++){
            imageG(i,j) = image(i,j)[1];
        }
    }
    imageB.setSize(image.getSizeX(),image.getSizeY(),1);
    for(int i=0;i<imageB.getSizeX();i++){
        for(int j=0;j<imageB.getSizeY();j++){
            imageB(i,j) = image(i,j)[2];
        }
    }

    treeR = TreeOfShape(imageR);
    treeG = TreeOfShape(imageG);
    treeB = TreeOfShape(imageB);

    std::cout << "fin construction color tree" << std::endl;
}
