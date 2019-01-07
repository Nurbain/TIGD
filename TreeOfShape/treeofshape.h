#ifndef TREEOFSHAPE_H
#define TREEOFSHAPE_H

#include "Common/Image.h"

class TreeOfShape
{
public:
    TreeOfShape(const char* filename);

    LibTIM::Image<LibTIM::U16> image;

    void interpolate();
};

#endif // TREEOFSHAPE_H
