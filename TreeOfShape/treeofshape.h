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

    std::vector<LibTIM::Point<LibTIM::TCoord>> R;
    std::vector<std::vector<LibTIM::Point<TCoord>>> parent;
    std::vector<std::vector<int>> area;
    void saveGraphe(const std::string& path) const;
    void removeShape(int seuil);

private:
    type_pixels median;

    LibTIM::Image<type_pixels> interpolate_image_min;
    LibTIM::Image<type_pixels> interpolate_image_max;

    void interpolate();

    void sort(LibTIM::Image<type_pixels>& result_img);
    std::vector<std::vector<LibTIM::Point<TCoord> > > union_find();
    void canonize_tree(LibTIM::Image<type_pixels>& f);
    bool is_in_image(LibTIM::Point<LibTIM::TCoord>& p);

    std::vector<LibTIM::Point<LibTIM::TCoord>> liste_fils(LibTIM::Point<LibTIM::TCoord>& p);

    void un_interpolate(LibTIM::Image<type_pixels>& f);

    type_pixels couleurParent(LibTIM::Point<TCoord>& p, int seuil);


    void compute_area();
    void medianCalcule();
};

#endif // TREEOFSHAPE_H
