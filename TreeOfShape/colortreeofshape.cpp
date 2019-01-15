#include "colortreeofshape.h"
#include "gradient.h"

colorTreeOfShape::colorTreeOfShape(const char *filename)
{
    image.load(filename);
    /*if(Image<int>::load(filename,image)){
        std::cout << "Image Load" <<std::endl;
    }else{
        std::cout << "Image Non Load y'a un prb" <<std::endl;
        return;
    }*/

    imageR.resize(image.width(),image.height(),1);
    for(int i=0;i<imageR.width();i++){
        for(int j=0;j<imageR.height();j++){
            imageR(i,j) = image(i,j,0,0);
        }
    }
    imageG.resize(image.width(),image.height(),1);
    for(int i=0;i<imageG.width();i++){
        for(int j=0;j<imageG.height();j++){
            imageG(i,j) = image(i,j,0,1);
        }
    }
    imageB.resize(image.width(),image.height(),1);
    for(int i=0;i<imageB.width();i++){
        for(int j=0;j<imageB.height();j++){
            imageB(i,j) = image(i,j,0,2);
        }
    }

    imageR.save("../result/rouge.pgm");
    imageG.save("../result/vert.pgm");
    imageB.save("../result/bleu.pgm");

    treeR = TreeOfShape(imageR);
    treeG = TreeOfShape(imageG);
    treeB = TreeOfShape(imageB);
    Gradient g;

    Image<result_type> gradientR = g.Sobel(imageR);
    Image<result_type> gradientG = g.Sobel(imageG);
    Image<result_type> gradientB = g.Sobel(imageB);

    gradientR.save("../result/GradientRouge.pgm");
    gradientG.save("../result/GradientVert.pgm");
    gradientB.save("../result/GradientBleu.pgm");


    Image<type_pixels> aireR;

    aireR.resize(imageR.width(),imageR.height(),1);
    for(int i=0;i<aireR.width();i++){
        for(int j=0;j<aireR.height();j++){
             aireR(i,j) = treeR.area[i][j];
        }
    }

    aireR.save("../result/aireR.pgm");

    Image<type_pixels> aireG;

    aireG.resize(imageR.width(),imageR.height(),1);
    for(int i=0;i<aireR.width();i++){
        for(int j=0;j<aireR.height();j++){
            aireG(i,j) = treeG.area[i][j];
        }
    }

    aireG.save("../result/aireG.pgm");

    Image<type_pixels> aireB;

    aireB.resize(imageR.width(),imageR.height(),1);
    for(int i=0;i<aireR.width();i++){
        for(int j=0;j<aireR.height();j++){
            aireB(i,j) = treeB.area[i][j];
        }
    }

    aireR.save("../result/aireB.pgm");

    imageMerge.resize(image.width(),image.height(),1);
    for(int i=0;i<imageMerge.width();i++){
        for(int j=0;j<imageMerge.height();j++){
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

    imageMerge.save("../result/aireM.pgm");

    treeMerge = TreeOfShape(imageMerge);

    std::cout << "fin construction color tree" << std::endl;
}



void colorTreeOfShape::removeShape(int seuil){

    Image<int> newImage = Image<int>(image.width(),image.height(),1,3);
    int r,g,b;
    for(int i=0;i<image.width();i++){
        for(int j=0;j<image.height();j++){
            if(treeMerge.area[i][j] < seuil){
                LibTIM::Point<LibTIM::TCoord> pix = LibTIM::Point<LibTIM::TCoord>(i,j);

                couleurParent(pix,seuil,r,g,b);
                newImage(i,j,0,0) = r;
                newImage(i,j,0,1) = g;
                newImage(i,j,0,2) = b;
            }else{
                r = image(i,j,0,0);
                g = image(i,j,0,1);
                b = image(i,j,0,2);
                newImage(i,j,0,0) = r;
                newImage(i,j,0,1) = g;
                newImage(i,j,0,2) = b;
            }
        }
    }

    newImage.save("../result/resultRemoveShape.pgm");
}


void colorTreeOfShape::couleurParent(LibTIM::Point<LibTIM::TCoord> &p, int seuil,int& r,int& g,int& b){

    LibTIM::Point<LibTIM::TCoord> pp = treeMerge.parent[p.x][p.y];

    if(pp.x == p.x && pp.y == p.y && treeMerge.area[pp.x][pp.y] < seuil ){
        r = image(pp.x,pp.y,0,0);
        g = image(pp.x,pp.y,0,1);
        b = image(pp.x,pp.y,0,2);
    }else if( treeMerge.area[pp.x][pp.y] < seuil){
        couleurParent(pp,seuil,r,g,b);
    }else{
        r = image(pp.x,pp.y,0,0);
        g = image(pp.x,pp.y,0,1);
        b = image(pp.x,pp.y,0,2);
    }

}
