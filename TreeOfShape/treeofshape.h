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

    LibTIM::Image<type_pixels> interpolate_image_min;
    LibTIM::Image<type_pixels> interpolate_image_max;

    void interpolate();

    void sort(LibTIM::Image<type_pixels>& result_img,std::vector<LibTIM::Point<LibTIM::TCoord>>& R);
    void medianCalcule();

};

#endif // TREEOFSHAPE_H
