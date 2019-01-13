#ifndef COLORTREEOFSHAPE_H
#define COLORTREEOFSHAPE_H

#include "treeofshape.h"


class colorTreeOfShape
{
public:
    colorTreeOfShape();

    Image<type_pixels> Image;


    Image<type_pixels> imageR;
    Image<type_pixels> imageG;
    Image<type_pixels> imageB;



    TreeOfShape treeR;
    TreeOfShape treeG;
    TreeOfShape treeB;

};

#endif // COLORTREEOFSHAPE_H
