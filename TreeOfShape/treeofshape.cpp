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

            interpolate_image_min((i*2+3)-1,(j*2+3)-1) = image(i,j); //From Image

            //Bords superieur
            if(i==0){
                interpolate_image_min((i*2+3)-2,(j*2+3)-1) = image(i,j) < interpolate_image_min((i*2+3)-3,(j*2+3)-1) ? image(i,j) : interpolate_image_min((i*2+3)-3,(j*2+3)-1) ; //Bord superieur
                interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j)<image(i,j+1) ? image(i,j) : image(i,j+1); //Colonne basse
                interpolate_image_min((i*2+3)-1,(j*2+3)-1) = image(i,j) < interpolate_image_min((i*2+3),(j*2+3)) ? image(i,j) : interpolate_image_min((i*2+3),(j*2+3)); //Diago droite haute
                if(j == image.getSizeY()-1){
                    interpolate_image_min((i*2+3),(j*2+3)-1) = image(i,j) < interpolate_image_min((i*2+3)+1,(j*2+3)-1) ? image(i,j) : interpolate_image_min((i*2+3)+1,(j*2+3)-1); //Ligne
                    interpolate_image_min((i*2+3),(j*2+3)) = image(i,j)< interpolate_image_min((i*2+3)+1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)+1,(j*2+3)+1); // Diago basse
                }else {

                    interpolate_image_min((i*2+3),(j*2+3)-1) = image(i,j) < image(i+1,j) ? image(i,j) : image(i+1,j); //Ligne
                    interpolate_image_min((i*2+3),(j*2+3)) = image(i,j)<image(i+1,j+1) ? image(i,j) : image(i+1,j+1); //Diagonnale basse

                    if(j == 0){
                        interpolate_image_min((i*2+3)-2,(j*2+3)-2) = image(i,j) < interpolate_image_min((i*2+3)-3,(j*2+3)-3) ? image(i,j) : interpolate_image_min((i*2+3)-3,(j*2+3)-3) ; //Diago gauche haute
                        interpolate_image_min((i*2+3)-2,(j*2+3)-1) = image(i,j) < interpolate_image_min((i*2+3)-3,(j*2+3)-1) ? image(i,j) : interpolate_image_min((i*2+3)-3,(j*2+3)-1) ; //Ligne derriere
                    }
                }

            }else if(j==0){

                interpolate_image_min((i*2+3)-2,(j*2+3)-2) = image(i,j) < interpolate_image_min((i*2+3)-3,(j*2+3)-3) ? image(i,j) : interpolate_image_min((i*2+3)-3,(j*2+3)-3) ; //Diago gauche haute
                interpolate_image_min((i*2+3)-2,(j*2+3)-1) = image(i,j) < interpolate_image_min((i*2+3)-3,(j*2+3)-1) ? image(i,j) : interpolate_image_min((i*2+3)-3,(j*2+3)-1) ; //Ligne derriere
                interpolate_image_min((i*2+3),(j*2+3)-1) = image(i,j) < image(i+1,j) ? image(i,j) : image(i+1,j); //Ligne

                if( i == image.getSizeX()-1){
                    interpolate_image_min((i*2+3)-2,(j*2+3)) =  image(i,j) < interpolate_image_min((i*2+3)-3,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)-3,(j*2+3)+1); //Diago gauche basse
                    interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j) < interpolate_image_min((i*2+3)-1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)-1,(j*2+3)+1); //Bord bas
                    interpolate_image_min((i*2+3),(j*2+3)) = image(i,j) < interpolate_image_min((i*2+3)+1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)+1,(j*2+3)+1); //Diago droite basse
                }else{
                    interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j)<image(i,j+1) ? image(i,j) : image(i,j+1); //Colonne basse
                    interpolate_image_min((i*2+3),(j*2+3)) = image(i,j)<image(i+1,j+1) ? image(i,j) : image(i+1,j+1); //Diagonnale basse
                }
            }else if( j == image.getSizeY()-1){
                interpolate_image_min((i*2+3),(j*2+3)-1) = image(i,j) < interpolate_image_min((i*2+3)+1,(j*2+3)-1) ? image(i,j) : interpolate_image_min((i*2+3)+1,(j*2+3)-1); //Ligne
                interpolate_image_min((i*2+3),(j*2+3)) = image(i,j)< interpolate_image_min((i*2+3)+1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)+1,(j*2+3)+1); // Diago basse

                if(i == image.getSizeX()-1){
                    interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j) < interpolate_image_min((i*2+3)-1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)-1,(j*2+3)+1); //Colonne basse
                }else{
                    interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j)<image(i,j+1) ? image(i,j) : image(i,j+1); //Colonne basse
                }
            }else if( i == image.getSizeX()-1){
                interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j) < interpolate_image_min((i*2+3)-1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)-1,(j*2+3)+1); //Bord bas
                interpolate_image_min((i*2+3),(j*2+3)) = image(i,j) < interpolate_image_min((i*2+3)+1,(j*2+3)+1) ? image(i,j) : interpolate_image_min((i*2+3)+1,(j*2+3)+1); //Diago droite basse
                interpolate_image_min((i*2+3),(j*2+3)-1) = image(i,j) < image(i+1,j) ? image(i,j) : image(i+1,j); //Ligne
            }else{
                interpolate_image_min((i*2+3),(j*2+3)-1) = image(i,j) < image(i+1,j) ? image(i,j) : image(i+1,j); //Ligne
                interpolate_image_min((i*2+3)-1,(j*2+3)) = image(i,j)<image(i,j+1) ? image(i,j) : image(i,j+1); //Colonne basse
                interpolate_image_min((i*2+3),(j*2+3)) = image(i,j)<image(i+1,j+1) ? image(i,j) : image(i+1,j+1); //Diagonnale basse
            }
        }
    }
}

bool is_empty(std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>>& q){
    bool result = true;

    int size = q.size();
    for(int i=0;i<size;i++){
        result = q[i].empty() && result;
    }
    return result;
}

void next_unempty(std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>>& q,type_pixels& l){
    int step = 1;
    if(is_empty(q))
        return;
    while(q[l].empty()){
        if(l+step < q.size() && !q[l+step].empty()){
            l = l+step;
            return;
        }
        if(l-step >= 0 && !q[l-step].empty()){
            l = l-step;
            return;
        }
        step++;
    }
}

LibTIM::Point<LibTIM::TCoord> priority_pop(std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>>& q,type_pixels& l){
    if(q[l].empty()){
        next_unempty(q,l);
    }
    LibTIM::Point<LibTIM::TCoord> result = q[l].front();
    q[l].pop();
    return result;
}

void priority_push(std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>>& q,LibTIM::Point<LibTIM::TCoord> h,LibTIM::Image<type_pixels>& im_min,LibTIM::Image<type_pixels>& im_max,type_pixels& l){
    type_pixels lower = im_min(h);
    type_pixels upper = im_max(h);
    int l2;
    if(lower > l){
        l2 = lower;
    }else{
        if(upper < l){
            l2 = upper;
        }else{
            l2 =l;
        }
    }
    q[l2].push(h);
}

std::vector<LibTIM::Point<LibTIM::TCoord>> get_voisinage(LibTIM::Point<LibTIM::TCoord>& p,LibTIM::Image<type_pixels>& im){
    std::vector<LibTIM::Point<LibTIM::TCoord>> result;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(p.x+i >=0 && p.x+i < im.getSizeX() && p.y+j >=0 && p.y+j < im.getSizeY())
                result.push_back(im(p.x+i,p.y+j));
        }
    }
    return result;
}

void TreeOfShape::sort(LibTIM::Image<type_pixels>& result_img,std::vector<LibTIM::Point<LibTIM::TCoord>>& R){
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

    while(!is_empty(hierarchical_queue)){
        LibTIM::Point<LibTIM::TCoord> h = priority_pop(hierarchical_queue,l);
        result_img(h) = l;
        R.push_back(h);
        std::vector<LibTIM::Point<LibTIM::TCoord>> voisins = get_voisinage(h,interpolate_image_max);
        for(auto& n:voisins){
            if(!deja_vu[n.x][n.y]){
                priority_push(hierarchical_queue,n,interpolate_image_min,interpolate_image_max,l);
                deja_vu[n.x][n.y] = true;
            }
        }
    }

}


LibTIM::Point<LibTIM::TCoord> find_root(std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>>& zpar,LibTIM::Point<LibTIM::TCoord>& x){
    LibTIM::Point<LibTIM::TCoord> p = zpar[x.x][x.y];
    if(p.x == x.x && p.y == x.y){
        return x;
    }
    zpar[x.x][x.y] = find_root(zpar,x);
    return zpar[x.x][x.y];
}

std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> TreeOfShape::union_find(std::vector<LibTIM::Point<LibTIM::TCoord>>& R){
    std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> zpar,parent;
    zpar.resize(interpolate_image_min.getSizeX());
    for(int i=0;i<interpolate_image_min.getSizeX();i++){
        zpar[i].resize(interpolate_image_min.getSizeY());
        for(int j=0;j<interpolate_image_min.getSizeY();j++){
            zpar[i][j] = LibTIM::Point<LibTIM::TCoord>(-1,-1);
        }
    }
    parent.resize(interpolate_image_min.getSizeX());
    for(int i=0;i<interpolate_image_min.getSizeX();i++){
        parent[i].resize(interpolate_image_min.getSizeY());
        for(int j=0;j<interpolate_image_min.getSizeY();j++){
            parent[i][j] = LibTIM::Point<LibTIM::TCoord>(-1,-1);
        }
    }

    for(int i=R.size()-1;i>0;i++){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        zpar[p.x][p.y] = p;
        parent[p.x][p.y] = p;
        std::vector<LibTIM::Point<LibTIM::TCoord>> voisins = get_voisinage(p,interpolate_image_max);
        for(auto& n:voisins){
            if(zpar[n.x][n.y].x != -1){
                LibTIM::Point<LibTIM::TCoord> r =find_root(zpar,n);
                if(p.x == r.x && p.y == r.y){
                    zpar[r.x][r.y] = p;
                    parent[r.x][r.y] = p;
                }
            }
        }
    }
    return parent;
}
