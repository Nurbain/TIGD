#ifndef TREEOFSHAPE_H
#define TREEOFSHAPE_H

#include "Common/Image.h"

class TreeOfShape
{
public:
    TreeOfShape(const char* filename);

    LibTIM::Image<LibTIM::U16> image;

    LibTIM::Image<LibTIM::U16> interpolate_image;

    void interpolate();

    void sort();
};

#endif // TREEOFSHAPE_H
