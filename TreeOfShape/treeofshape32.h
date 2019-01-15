#ifndef TREEOFSHAPE32_H
#define TREEOFSHAPE32_H


#include "Common/Image.h"

using namespace LibTIM;
using pixels32 = LibTIM::U16;

class TreeOfShape32
{
public:
    TreeOfShape32(){}
    TreeOfShape32(Image<pixels32> &img);
    Image<pixels32> image;

    std::vector<LibTIM::Point<LibTIM::TCoord>> R;
    std::vector<std::vector<LibTIM::Point<TCoord>>> parent;
    std::vector<std::vector<int>> area;
    void saveGraphe(const std::string& path) const;
    void removeShape(int seuil);

private:
    pixels32 median;

    LibTIM::Image<pixels32> interpolate_image_min;
    LibTIM::Image<pixels32> interpolate_image_max;

    void interpolate();

    void sort(LibTIM::Image<pixels32>& result_img);
    std::vector<std::vector<LibTIM::Point<TCoord> > > union_find();
    void canonize_tree(LibTIM::Image<pixels32>& f);
    bool is_in_image(LibTIM::Point<LibTIM::TCoord>& p);

    std::vector<LibTIM::Point<LibTIM::TCoord>> liste_fils(LibTIM::Point<LibTIM::TCoord>& p);

    void un_interpolate(LibTIM::Image<pixels32>& f);

    pixels32 couleurParent(LibTIM::Point<TCoord>& p, int seuil);


    void compute_area(LibTIM::Image<pixels32> &f);
    void medianCalcule();
};

#endif // TREEOFSHAPE32_H
