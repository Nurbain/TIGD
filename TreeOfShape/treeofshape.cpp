#include "treeofshape.h"

#include <vector>
#include <algorithm>

TreeOfShape::TreeOfShape(const char *filename)
{
    if(LibTIM::Image<type_pixels>::load(filename,image)){
        std::cout << "Image Load" <<std::endl;
    }else{
        std::cout << "Image Non Load y'a un prb" <<std::endl;
    }
}

void TreeOfShape::medianCalcule(){
    std::vector<type_pixels> medianVec;

    for(int i=0;i<image.getSizeX();i++){
        medianVec.push_back(image(i,0));
        medianVec.push_back(image(i,image.getSizeY()-1));
    }

    for(int i=1;i<image.getSizeY()-1;i++){
        medianVec.push_back(image(0,i));
        medianVec.push_back(image(image.getSizeX()-1,i));
    }


    std::nth_element(medianVec.begin(), medianVec.begin() + medianVec.size()/2, medianVec.end());
    median = medianVec[medianVec.size()/2];

}

void TreeOfShape::interpolate(){

    interpolate_image_min.setSize(image.getSizeX()*2+3,image.getSizeY()*2+3,0);
    interpolate_image_max.setSize(image.getSizeX()*2+3,image.getSizeY()*2+3,0);

    //Fill with median in external border
    // interpolate_image_max.size = interpolate_image_min.size
    for(int i=0;i<interpolate_image_min.getSizeX();i++){
        interpolate_image_min(i,0) = median;
        interpolate_image_min(i,interpolate_image_min.getSizeY()-1) = median;

        interpolate_image_max(i,0) = median;
        interpolate_image_max(i,interpolate_image_min.getSizeY()-1) = median;
    }

    for(int i=1;i<interpolate_image_min.getSizeY()-1;i++){
        interpolate_image_min(0,i) = median;
        interpolate_image_min(interpolate_image_min.getSizeX()-1,i) = median;

        interpolate_image_max(0,i) = median;
        interpolate_image_max(interpolate_image_min.getSizeX()-1,i) = median;
    }



    for(int i = 0; i<image.getSizeX(); i++){
        for(int j=0; j<image.getSizeY();j++){

            //Bords image superieur
            if(i==0){

            }else if(j==image.getSizeY()-1){ //Bords image droite


            }else if(i==image.getSizeX()-1){ //Bords image inferieur

            }else if(j==0){ //bords gauche


            }else{ //Non Bords


            }
        }
    }

}

void TreeOfShape::sort(){
    std::vector<std::vector<bool>> deja_vu;
    deja_vu.resize(interpolate_image_min.getSizeX());
    for(int i=0;i<interpolate_image_min.getSizeX();i++){
        deja_vu[i].resize(interpolate_image_min.getSizeY());
        for(int j=0;j<interpolate_image_min.getSizeY();j++){
            deja_vu[i][j] = false;
        }
    }
    std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>> hierarchical_queue;
    hierarchical_queue.resize(interpolate_image_max.getMax());

    hierarchical_queue[interpolate_image_max(0,0)].push(LibTIM::Point<LibTIM::TCoord>(0,0));
    deja_vu[0][0] = true;

    type_pixels l = interpolate_image_max(0,0);


}
