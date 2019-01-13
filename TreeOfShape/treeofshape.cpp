#include "treeofshape.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

TreeOfShape::TreeOfShape(const char *filename)
{
    if(LibTIM::Image<type_pixels>::load(filename,image)){
        std::cout << "Image Load" <<std::endl;
    }else{
        std::cout << "Image Non Load y'a un prb" <<std::endl;
        return;
    }
    medianCalcule();
    interpolate();
    LibTIM::Image<type_pixels> result;
    sort(result);
    union_find();
    canonize_tree(result);
    un_interpolate(result);
    compute_area();
    std::cout << "fin construction tree" << std::endl;
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

    //Nouvelle Image avec Medianne
    Image<type_pixels> newImage = Image<type_pixels>(image.getSizeX()+2,image.getSizeY()+2);

    for(int i=0;i<newImage.getSizeX();i++){
        for(int j=0;j<newImage.getSizeY();j++){
            if( i == 0 || j == 0 || i == newImage.getSizeX()-1 || j == newImage.getSizeY()-1)
               newImage(i,j) = median;
            else
               newImage(i,j) = image(i-1,j-1);
        }
    }

    /*image.setSize(newImage.getSizeX(),newImage.getSizeY(),1);
    for(int i=0;i<image.getSizeX();i++){
        for(int j=0;j<image.getSizeY();j++){
            image(i,j) = newImage(i,j);
        }
    }*/

    interpolate_image_min = Image<type_pixels>(newImage.getSizeX()*4-1,newImage.getSizeY()*4-1);
    interpolate_image_max = Image<type_pixels>(newImage.getSizeX()*4-1,newImage.getSizeY()*4-1);

    //Dim 2
    for(int i = 0; i<newImage.getSizeX(); i++){
        for(int j=0; j<newImage.getSizeY();j++){
            interpolate_image_min(i*4+1,j*4+1) = newImage(i,j); //From Image
            interpolate_image_max(i*4+1,j*4+1) = newImage(i,j);


            if(j !=newImage.getSizeY()-1 && i !=newImage.getSizeX()-1){
                interpolate_image_min((i*4+3),(j*4+3)) = newImage(i,j) > newImage(i+1,j+1) ? newImage(i,j) : newImage(i+1,j+1); //Diago basse droite
                interpolate_image_max((i*4+3),(j*4+3)) = newImage(i,j) > newImage(i+1,j+1) ? newImage(i,j) : newImage(i+1,j+1);
            }
            if(i !=newImage.getSizeX()-1){
                interpolate_image_min(i*4+3,j*4+1) = newImage(i,j) > newImage(i+1,j) ? newImage(i,j) : newImage(i+1,j); //Ligne Droite
                interpolate_image_max(i*4+3,j*4+1) = newImage(i,j) > newImage(i+1,j) ? newImage(i,j) : newImage(i+1,j);
            }
            if(j !=newImage.getSizeY()-1){
                interpolate_image_min(i*4+1,j*4+3) = newImage(i,j) > newImage(i,j+1) ? newImage(i,j) : newImage(i,j+1); //Colonne Basse
                interpolate_image_max(i*4+1,j*4+3) = newImage(i,j) > newImage(i,j+1) ? newImage(i,j) : newImage(i,j+1);
            }
        }
    }

    //Dim 1
    for(int i = 1; i<interpolate_image_min.getSizeX(); i=i+2){
        for(int j=1; j<interpolate_image_min.getSizeY();j=j+2){

            if(j !=interpolate_image_min.getSizeY()-2){
                interpolate_image_min(i,j+1) = interpolate_image_min(i,j) < interpolate_image_min(i,j+2) ? interpolate_image_min(i,j) : interpolate_image_min(i,j+2); //Ligne Droite
                interpolate_image_max(i,j+1) = interpolate_image_max(i,j) > interpolate_image_max(i,j+2) ? interpolate_image_max(i,j) : interpolate_image_max(i,j+2); //Ligne Droite
            }

            if(i !=interpolate_image_min.getSizeX()-2){
                interpolate_image_min(i+1,j) = interpolate_image_min(i,j) < interpolate_image_min(i+2,j) ? interpolate_image_min(i,j) : interpolate_image_min(i+2,j); //Colonne Basse
                interpolate_image_max(i+1,j) = interpolate_image_max(i,j) > interpolate_image_max(i+2,j) ? interpolate_image_max(i,j) : interpolate_image_max(i+2,j); //Colonne Basse
            }
        }
    }

    //Dim 1 Exterieur
    for(int i = 0; i<interpolate_image_min.getSizeX(); i++){
        for(int j=0; j<interpolate_image_min.getSizeY();j++){

            if(i==0){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }else if(j==0){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }else if(i==interpolate_image_min.getSizeX()-1){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }else if(j==interpolate_image_min.getSizeY()-1){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }
        }
    }

    //Dim 0
    for(int i = 2; i<interpolate_image_min.getSizeX()-1; i=i+2){
        for(int j=2; j<interpolate_image_min.getSizeY()-1;j=j+2){
            type_pixels minInterval1 = std::min(interpolate_image_min(i-1,j),interpolate_image_min(i+1,j));
            type_pixels minInterval2 = std::min(interpolate_image_min(i,j-1),interpolate_image_min(i,j+1));
            interpolate_image_min(i,j) = std::min(minInterval1,minInterval2);

            type_pixels maxInterval1 = std::max(interpolate_image_max(i-1,j),interpolate_image_max(i+1,j));
            type_pixels maxInterval2 = std::max(interpolate_image_max(i,j-1),interpolate_image_max(i,j+1));
            interpolate_image_max(i,j) = std::min(maxInterval1,maxInterval2);
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
        if(i==0)
            continue;
        if(p.x+i >=0 && p.x+i < im.getSizeX())
            result.push_back(LibTIM::Point<LibTIM::TCoord>(p.x+i,p.y));
        if(p.y+i >=0 && p.y+i < im.getSizeY())
            result.push_back(LibTIM::Point<LibTIM::TCoord>(p.x,p.y+i));
    }
    return result;
}

void TreeOfShape::sort(LibTIM::Image<type_pixels>& result_img){
    result_img.setSize(interpolate_image_max.getSizeX(),interpolate_image_max.getSizeY(),1);
    std::vector<std::vector<bool>> deja_vu;
    deja_vu.resize(interpolate_image_min.getSizeX());
    for(int i=0;i<interpolate_image_min.getSizeX();i++){
        deja_vu[i].resize(interpolate_image_min.getSizeY());
        for(int j=0;j<interpolate_image_min.getSizeY();j++){
            deja_vu[i][j] = false;
        }
    }
    std::vector<std::queue<LibTIM::Point<LibTIM::TCoord>>> hierarchical_queue;
    hierarchical_queue.resize(interpolate_image_max.getMax()+1);

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
    zpar[x.x][x.y] = find_root(zpar,zpar[x.x][x.y]);
    return zpar[x.x][x.y];
}

std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> TreeOfShape::union_find(){
    std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> zpar;
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

    for(int i=R.size()-1;i>=0;i--){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        zpar[p.x][p.y] = p;
        parent[p.x][p.y] = p;
        std::vector<LibTIM::Point<LibTIM::TCoord>> voisins = get_voisinage(p,interpolate_image_max);
        for(auto& n:voisins){
            if(zpar[n.x][n.y].x != -1){
                LibTIM::Point<LibTIM::TCoord> r =find_root(zpar,n);
                if(p.x != r.x || p.y != r.y){
                    zpar[r.x][r.y] = p;
                    parent[r.x][r.y] = p;
                }
            }
        }
    }
    return parent;
}

void TreeOfShape::canonize_tree(LibTIM::Image<type_pixels>& f){
    for(unsigned i=0;i<R.size();i++){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
        if(f(parent[q.x][q.y]) == f(q)){
            parent[p.x][p.y] = parent[q.x][q.y];
        }
    }
}

bool TreeOfShape::is_in_image(LibTIM::Point<LibTIM::TCoord>& p){
    LibTIM::TCoord x = p.x,y=p.y;
    if(x == 1 || y == 1 || x == interpolate_image_max.getSizeX()-2 || y == interpolate_image_max.getSizeY()-2){
        return false;
    }
    x-=1;
    y-=1;
    return (x%4) == 0 && (y%4) == 0;
}

std::vector<LibTIM::Point<LibTIM::TCoord>> TreeOfShape::liste_fils(LibTIM::Point<LibTIM::TCoord>& p){
    std::vector<LibTIM::Point<LibTIM::TCoord>> result;

    for(int i=0;i<interpolate_image_min.getSizeX();i++){
        for(int j=0;j<interpolate_image_min.getSizeY();j++){
            LibTIM::Point<LibTIM::TCoord> q = parent[i][j];
            if(i == p.x && j == q.y)
                continue;
            if(q.x == p.x && q.y == p.y){
                result.push_back(LibTIM::Point<LibTIM::TCoord>(i,j));
            }
        }
    }

    return result;
}


void TreeOfShape::un_interpolate(LibTIM::Image<type_pixels> &f){
    for(unsigned i=0;i<R.size();i++){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        if(is_in_image(p)){
            LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
            if(!is_in_image(q) && f(p) == f(q)){
                std::vector<LibTIM::Point<LibTIM::TCoord>> freres = liste_fils(q);
                for(auto& f:freres){
                    parent[f.x][f.y] = p;
                }
                parent[p.x][p.y] = parent[q.x][q.y];
                if(parent[q.x][q.y].x == q.x && parent[q.x][q.y].y == q.y)
                    parent[p.x][p.y] = p;
                parent[q.x][q.y] = q;
            }

        }
    }

    std::vector<std::vector<LibTIM::Point<TCoord>>> parent_clean;
    std::vector<LibTIM::Point<LibTIM::TCoord>> R_clean;

    parent_clean.resize(image.getSizeX());
    for(int i=0;i<image.getSizeX();i++){
        parent_clean[i].resize(image.getSizeY());
        for(int j=0;j<image.getSizeY();j++){
            parent_clean[i][j] = LibTIM::Point<LibTIM::TCoord>(-1,-1);
        }
    }

    for(unsigned i=0;i<R.size();i++){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        if(is_in_image(p)){
            R_clean.push_back(LibTIM::Point<LibTIM::TCoord>(((p.x-1)/4)-1,((p.y-1)/4)-1));
            LibTIM::Point<LibTIM::TCoord> q = LibTIM::Point<LibTIM::TCoord>(((parent[p.x][p.y].x-1)/4)-1,((parent[p.x][p.y].y-1)/4)-1);
            parent_clean[((p.x-1)/4)-1][((p.y-1)/4)-1] = q;
        }
    }

    R = R_clean;
    parent = parent_clean;
}

void TreeOfShape::saveGraphe(const std::string& path) const{
    //On ouvre le fichier en lecture
    std::ofstream file(path,std::ios::out | std::ios::trunc);

    //Si le fichier n'est pas ouvert on quitte
    if(file){
        file << "strict graph {" << std::endl;
        for(uint x=0;x<parent.size();x++){
            for(uint y=0;y<parent[x].size();y++){
                file << "\"(" << parent[x][y].x << "," << parent[x][y].y << ")\" -- \"(" << x << "," << y << ")\"" << std::endl;
            }
        }
        file << "}" << std::endl;
        file.close();
    }
}

void TreeOfShape::compute_area(){
    area.resize(image.getSizeX());
    for(int i=0;i<image.getSizeX();i++){
        area[i].resize(image.getSizeY());
        for(int j=0;j<image.getSizeY();j++){
            area[i][j] = 1;
        }
    }

    for(int i=R.size()-1;i>=0;i--){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
        area[q.x][q.y] += area[p.x][p.y];
    }

}
