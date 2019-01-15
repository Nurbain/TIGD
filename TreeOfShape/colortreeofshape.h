#ifndef COLORTREEOFSHAPE_H
#define COLORTREEOFSHAPE_H

#include "treeofshape.h"
#include "treeofshape32.h"

using namespace LibTIM;

class colorTreeOfShape
{
public:
    colorTreeOfShape(const char *filename);

    Image<RGB> image;


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
    RGB couleurParent(LibTIM::Point<TCoord> &p, int seuil);
};

#endif // COLORTREEOFSHAPE_H
