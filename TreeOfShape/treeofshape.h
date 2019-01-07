#ifndef TREEOFSHAPE_H
#define TREEOFSHAPE_H

#include "Common/Image.h"

using namespace LibTIM;
using type_pixels = LibTIM::U8;

class TreeOfShape
{
public:
    TreeOfShape(const char* filename);

    Image<type_pixels> image;
    type_pixels median;

    LibTIM::Image<type_pixels> interpolate_image;

    void interpolate();

    void sort();
    void medianCalcule();
    void interpolate();

};

#endif // TREEOFSHAPE_H
