#include "treeofshape.h"
#include <iostream>

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
