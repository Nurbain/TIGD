#include "gradient.h"

Image<type_pixels> Gradient::Sobel(const Image<type_pixels>& img){
    int Sobel3x[9]={-1,0,1,
                        -2,0,2,
                        -1,0,1};


    int Sobel3y[9]={-1,-2,-1,
                        0,0,0,
                        1,2,1};
    Image<type_pixels> result = Image<type_pixels>(img.getSizeX(),img.getSizeY());

    int n = 1,size=3;
    for(uint i=0;i<result.getSizeX();i++){
        for(uint j = 0;j<result.getSizeY();j++){
            int interX = 0,interY = 0;
            for(int x=-n;x<size-n;x++){
                for(int y=-n;y<size-n;y++){
                    if(i+x < 0 || j+y < 0 || i+x >= result.getSizeX() || j+y >= result.getSizeY())
                        continue;
                    interX += img(i+x,j+y)*Sobel3x[(n+x)+(n+y)*3];
                    interY += img(i+x,j+y)*Sobel3y[(n+x)+(n+y)*3];
                }
            }
            result(i,j) = std::sqrt(interX*interX+interY*interY);
        }

    }

    return result;
}
