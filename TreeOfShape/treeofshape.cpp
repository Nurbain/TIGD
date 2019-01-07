#include "treeofshape.h"

TreeOfShape::TreeOfShape(const char *filename)
{

    if(LibTIM::Image<LibTIM::U16>::load(filename,image)){
        std::cout << "Image Load" <<std::endl;
    }else{
        std::cout << "Image Non Load y'a un prb" <<std::endl;
    }

}


void TreeOfShape::interpolate(){

}

void TreeOfShape::sort(){
    std::vector<std::vector<bool>> deja_vu;
    deja_vu.resize(interpolate_image.getSizeX());
    for(int i=0;i<interpolate_image.getSizeX();i++){
        deja_vu[i].resize(interpolate_image.getSizeY());
        for(int j=0;j<interpolate_image.getSizeY();j++){
            deja_vu[i][j] = false;
        }
    }
    std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>> kjhvkdjs;


}
