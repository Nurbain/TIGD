#ifndef COLORTREEOFSHAPE_H
#define COLORTREEOFSHAPE_H

#include "treeofshape.h"

class colorTreeOfShape
{
public:
    colorTreeOfShape(const char *filename);

    Image<int> image;


    Image<type_pixels> imageR;
    Image<type_pixels> imageG;
    Image<type_pixels> imageB;
    Image<type_pixels> imageMerge;



    TreeOfShape treeR;
    TreeOfShape treeG;
    TreeOfShape treeB;
    TreeOfShape treeMerge;

    void removeShape(int seuil);

private:
    void couleurParent(LibTIM::Point<LibTIM::TCoord> &p, int seuil,int& r,int& g,int& b);
};

#endif // COLORTREEOFSHAPE_H
