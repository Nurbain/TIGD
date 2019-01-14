#ifndef COLORTREEOFSHAPE_H
#define COLORTREEOFSHAPE_H

#include "treeofshape.h"

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




};

#endif // COLORTREEOFSHAPE_H
