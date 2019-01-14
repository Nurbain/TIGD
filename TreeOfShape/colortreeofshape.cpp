#include "colortreeofshape.h"
#include "gradient.h"

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

    imageR.save("../rouge.pgm");
    imageG.save("../vert.pgm");
    imageB.save("../bleu.pgm");

    treeR = TreeOfShape(imageR);
    treeG = TreeOfShape(imageG);
    treeB = TreeOfShape(imageB);
    Gradient g;

    Image<type_pixels> gradientR = g.Sobel(imageR);
    Image<type_pixels> gradientG = g.Sobel(imageG);
    Image<type_pixels> gradientB = g.Sobel(imageB);

    gradientR.save("../GradientRouge.pgm");
    gradientG.save("../GradientVert.pgm");
    gradientB.save("../GradientBleu.pgm");


    Image<type_pixels> aireR;

    aireR.setSize(imageR.getSizeX(),imageR.getSizeY(),1);
    for(int i=0;i<aireR.getSizeX();i++){
        for(int j=0;j<aireR.getSizeY();j++){
            aireR(i,j) = treeR.area[i][j];
        }
    }

    aireR.save("../aireR.pgm");

    Image<type_pixels> aireG;

    aireG.setSize(imageR.getSizeX(),imageR.getSizeY(),1);
    for(int i=0;i<aireR.getSizeX();i++){
        for(int j=0;j<aireR.getSizeY();j++){
            aireG(i,j) = treeG.area[i][j];
        }
    }

    aireG.save("../aireG.pgm");

    Image<type_pixels> aireB;

    aireB.setSize(imageR.getSizeX(),imageR.getSizeY(),1);
    for(int i=0;i<aireR.getSizeX();i++){
        for(int j=0;j<aireR.getSizeY();j++){
            aireB(i,j) = treeB.area[i][j];
        }
    }

    aireR.save("../aireB.pgm");

    imageMerge.setSize(image.getSizeX(),image.getSizeY(),1);
    for(int i=0;i<imageMerge.getSizeX();i++){
        for(int j=0;j<imageMerge.getSizeY();j++){
            if(gradientR(i,j)>gradientG(i,j)){
                if(gradientR(i,j)>gradientB(i,j)){
                    imageMerge(i,j) = treeR.area[i][j];
                }else{
                    imageMerge(i,j) = treeB.area[i][j];
                }
            }else{
                if(gradientG(i,j)>gradientB(i,j)){
                    imageMerge(i,j) = treeG.area[i][j];
                }else{
                    imageMerge(i,j) = treeB.area[i][j];
                }
            }
        }
    }

    treeMerge = TreeOfShape(imageMerge);

    std::cout << "fin construction color tree" << std::endl;
}



void colorTreeOfShape::removeShape(int seuil){

    Image<RGB> newImage = Image<RGB>(image.getSizeX(),image.getSizeY());

    for(int i=0;i<image.getSizeX();i++){
        for(int j=0;j<image.getSizeY();j++){
            if(treeMerge.area[i][j] < seuil){
                LibTIM::Point<TCoord> pix = LibTIM::Point<TCoord>(i,j);
                newImage(i,j) = couleurParent(pix,seuil);
            }else{
                newImage(i,j) = image(i,j);
            }
        }
    }

    newImage.save("../resultRemoveShape.pgm");
}


RGB colorTreeOfShape::couleurParent(LibTIM::Point<TCoord> &p, int seuil){

    LibTIM::Point<TCoord> pp = treeMerge.parent[p.x][p.y];

    if(pp.x == p.x && pp.y == p.y && treeMerge.area[pp.x][pp.y] < seuil ){
        return image(pp.x,pp.y);
    }else if( treeMerge.area[pp.x][pp.y] < seuil){
        return couleurParent(pp,seuil);
    }else{
        return image(pp.x,pp.y);
    }

}

