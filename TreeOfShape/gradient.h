#ifndef GRADIENT_H
#define GRADIENT_H

#include "Common/Image.h"
#include <math.h>

using namespace LibTIM;
template<typename T>
class Gradient
{
public:
    Gradient() = delete;
    static const int Sobel5x[25];

    static const int Sobel5y[25];

    static Image<T> Sobel(const Image<T>& img){
        Image<T> result = Image<T>(img.getSizeX(),img.getSizeY());;

        int n = 2,size=5;
        for(uint i=0;i<result.getSizeX();i++){
            for(uint j = 0;j<result.getSizeY();j++){
                int interX = 0,interY = 0;
                for(int x=-n;x<size-n;x++){
                    for(int y=-n;y<size-n;y++){
                        if(i+x < 0 || j+y < 0 || i+x >= result.getSizeX() || j+y >= result.getSizeY())
                            continue;
                        interX += img(i+x,j+y)*Sobel5x[(n+x)+(n+y)*5];
                        interY += img(i+x,j+y)*Sobel5y[(n+x)+(n+y)*5];
                    }
                }
                result(i,j) = std::sqrt(interX*interX + interY*interY);
            }

        }

        return result;
    }
};

template<typename T>
const int Gradient<T>::Sobel5x[25]={1,2,0,-2,-1,
                                      4,8,0,-8,-4,
                                      6,12,0,-12,-6,
                                      4,8,0,-8,-4,
                                      1,2,0,-2,-1};

template<typename T>
const int Gradient<T>::Sobel5y[25]={1, 4, 6, 4, 1,
                                      2, 8, 12, 8, 2,
                                      0, 0, 0, 0, 0,
                                      -2,-8,-12,-8,-2,
                                      -1,-4,-6,-4,-1};

#endif // GRADIENT_H
