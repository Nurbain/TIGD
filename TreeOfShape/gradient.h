#ifndef GRADIENT_H
#define GRADIENT_H

#include "Common/Image.h"
#include "treeofshape.h"
#include <math.h>

using namespace LibTIM;

using result_type = U8;
class Gradient
{
public:
    Gradient(){}

    Image<result_type> Sobel(const Image<type_pixels>& img);
};


#endif // GRADIENT_H
