#ifndef TREEOFSHAPE_H
#define TREEOFSHAPE_H

#include "Common/Image.h"

using namespace LibTIM;

class TreeOfShape
{
public:
    TreeOfShape(const char* filename);

    Image<U8> image;
    U8 median;

    LibTIM::Image<LibTIM::U16> interpolate_image;

    void interpolate();

    void sort();
    void medianCalcule();
    void interpolate();

};

#endif // TREEOFSHAPE_H
