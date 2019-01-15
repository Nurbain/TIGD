#ifndef TREEOFSHAPE_H
#define TREEOFSHAPE_H

#include "Common/Image.h"
#include "CImg.h"
#include <vector>
#include <queue>
#include <map>


//using namespace LibTIM;
using namespace cimg_library;
using type_pixels = int;
template <typename T>
using Image = CImg<T>;

class TreeOfShape
{
public:
    TreeOfShape(){}
    TreeOfShape(Image<type_pixels> &img);

    TreeOfShape(const char* filename);

    Image<type_pixels> image;

    std::vector<LibTIM::Point<LibTIM::TCoord>> R;
    std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> parent;
    std::vector<std::vector<int>> area;
    void saveGraphe(const std::string& path) const;
    void removeShape(int seuil);

private:

    bool is_empty(std::map<int,std::queue<LibTIM::Point<LibTIM::TCoord>>>& q);
    void next_unempty(std::map<int, std::queue<LibTIM::Point<LibTIM::TCoord> > > &q, type_pixels& l);
    LibTIM::Point<LibTIM::TCoord> priority_pop(std::map<int, std::queue<LibTIM::Point<LibTIM::TCoord> > > &q, type_pixels& l);
    void priority_push(std::map<int, std::queue<LibTIM::Point<LibTIM::TCoord> > > &q, LibTIM::Point<LibTIM::TCoord> h, Image<type_pixels>& im_min, Image<type_pixels>& im_max, type_pixels& l);
    std::vector<LibTIM::Point<LibTIM::TCoord>> get_voisinage(LibTIM::Point<LibTIM::TCoord>& p,Image<type_pixels>& im);
    LibTIM::Point<LibTIM::TCoord> find_root(std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>>& zpar,LibTIM::Point<LibTIM::TCoord>& x);
    type_pixels median;

    Image<type_pixels> interpolate_image_min;
    Image<type_pixels> interpolate_image_max;

    void interpolate();

    void sort(Image<type_pixels>& result_img);
    std::vector<std::vector<LibTIM::Point<LibTIM::TCoord> > > union_find();
    void canonize_tree(Image<type_pixels>& f);
    bool is_in_image(LibTIM::Point<LibTIM::TCoord>& p);

    std::vector<LibTIM::Point<LibTIM::TCoord>> liste_fils(LibTIM::Point<LibTIM::TCoord>& p);

    void un_interpolate(Image<type_pixels>& f);

    type_pixels couleurParent(LibTIM::Point<LibTIM::TCoord>& p, int seuil);


    void compute_area(Image<type_pixels> &f);
    void medianCalcule();
};

#endif // TREEOFSHAPE_H
