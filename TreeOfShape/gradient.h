#ifndef GRADIENT_H
#define GRADIENT_H

#include "treeofshape.h"
#include <math.h>



using result_type = type_pixels;
class Gradient
{
public:
    Gradient(){}

    Image<result_type> Sobel(const Image<type_pixels>& img);
};


#endif // GRADIENT_H
