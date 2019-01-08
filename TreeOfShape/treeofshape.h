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

    std::vector<LibTIM::Point<LibTIM::TCoord>> R;
    std::vector<std::vector<LibTIM::Point<TCoord>>> parent;

    void interpolate();

    void sort(LibTIM::Image<type_pixels>& result_img);
    std::vector<std::vector<LibTIM::Point<TCoord> > > union_find();
    void canonize_tree(LibTIM::Image<type_pixels>& f);
    bool is_in_image(LibTIM::Point<LibTIM::TCoord>& p);

    std::vector<LibTIM::Point<LibTIM::TCoord>> liste_fils(LibTIM::Point<LibTIM::TCoord>& p);

    void un_interpolate();

    void medianCalcule();

};

#endif // TREEOFSHAPE_H
