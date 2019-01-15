#include "treeofshape.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>


TreeOfShape::TreeOfShape(const char *filename)
{
    image.load(filename);
    /*if(Image<type_pixels>::load(filename,image)){
        std::cout << "Image Load" <<std::endl;
    }else{
        std::cout << "Image Non Load y'a un prb" <<std::endl;
        return;
    }*/
    medianCalcule();
    interpolate();
    Image<type_pixels> result;
    sort(result);
    union_find();
    canonize_tree(result);
    un_interpolate(result);
    compute_area(result);
    std::cout << "fin construction tree" << std::endl;
}

TreeOfShape::TreeOfShape(Image<type_pixels>& img):image(img){
    medianCalcule();
    interpolate();
    Image<type_pixels> result;
    sort(result);
    union_find();
    canonize_tree(result);
    un_interpolate(result);
    compute_area(result);
    std::cout << "fin construction tree" << std::endl;
}

void TreeOfShape::medianCalcule(){
    std::vector<type_pixels> medianVec;

    for(int i=0;i<image.width();i++){
        medianVec.push_back(image(i,0));
        medianVec.push_back(image(i,image.height()-1));
    }

    for(int i=1;i<image.height()-1;i++){
        medianVec.push_back(image(0,i));
        medianVec.push_back(image(image.width()-1,i));
    }


    std::nth_element(medianVec.begin(), medianVec.begin() + medianVec.size()/2, medianVec.end());
    median = medianVec[medianVec.size()/2];

}

void TreeOfShape::interpolate(){

    //Nouvelle Image avec Medianne
    Image<type_pixels> newImage = Image<type_pixels>(image.width()+2,image.height()+2);

    for(int i=0;i<newImage.width();i++){
        for(int j=0;j<newImage.height();j++){
            if( i == 0 || j == 0 || i == newImage.width()-1 || j == newImage.height()-1)
               newImage(i,j) = median;
            else
               newImage(i,j) = image(i-1,j-1);
        }
    }

    /*image.setSize(newImage.width(),newImage.height(),1);
    for(int i=0;i<image.width();i++){
        for(int j=0;j<image.height();j++){
            image(i,j) = newImage(i,j);
        }
    }*/

    interpolate_image_min = Image<type_pixels>(newImage.width()*4-1,newImage.height()*4-1);
    interpolate_image_max = Image<type_pixels>(newImage.width()*4-1,newImage.height()*4-1);

    //Dim 2
    for(int i = 0; i<newImage.width(); i++){
        for(int j=0; j<newImage.height();j++){
            interpolate_image_min(i*4+1,j*4+1) = newImage(i,j); //From Image
            interpolate_image_max(i*4+1,j*4+1) = newImage(i,j);


            if(j !=newImage.height()-1 && i !=newImage.width()-1){
                interpolate_image_min((i*4+3),(j*4+3)) = newImage(i,j) > newImage(i+1,j+1) ? newImage(i,j) : newImage(i+1,j+1); //Diago basse droite
                interpolate_image_max((i*4+3),(j*4+3)) = newImage(i,j) > newImage(i+1,j+1) ? newImage(i,j) : newImage(i+1,j+1);
            }
            if(i !=newImage.width()-1){
                interpolate_image_min(i*4+3,j*4+1) = newImage(i,j) > newImage(i+1,j) ? newImage(i,j) : newImage(i+1,j); //Ligne Droite
                interpolate_image_max(i*4+3,j*4+1) = newImage(i,j) > newImage(i+1,j) ? newImage(i,j) : newImage(i+1,j);
            }
            if(j !=newImage.height()-1){
                interpolate_image_min(i*4+1,j*4+3) = newImage(i,j) > newImage(i,j+1) ? newImage(i,j) : newImage(i,j+1); //Colonne Basse
                interpolate_image_max(i*4+1,j*4+3) = newImage(i,j) > newImage(i,j+1) ? newImage(i,j) : newImage(i,j+1);
            }
        }
    }

    //Dim 1
    for(int i = 1; i<interpolate_image_min.width(); i=i+2){
        for(int j=1; j<interpolate_image_min.height();j=j+2){

            if(j !=interpolate_image_min.height()-2){
                interpolate_image_min(i,j+1) = interpolate_image_min(i,j) < interpolate_image_min(i,j+2) ? interpolate_image_min(i,j) : interpolate_image_min(i,j+2); //Ligne Droite
                interpolate_image_max(i,j+1) = interpolate_image_max(i,j) > interpolate_image_max(i,j+2) ? interpolate_image_max(i,j) : interpolate_image_max(i,j+2); //Ligne Droite
            }

            if(i !=interpolate_image_min.width()-2){
                interpolate_image_min(i+1,j) = interpolate_image_min(i,j) < interpolate_image_min(i+2,j) ? interpolate_image_min(i,j) : interpolate_image_min(i+2,j); //Colonne Basse
                interpolate_image_max(i+1,j) = interpolate_image_max(i,j) > interpolate_image_max(i+2,j) ? interpolate_image_max(i,j) : interpolate_image_max(i+2,j); //Colonne Basse
            }
        }
    }

    //Dim 1 Exterieur
    for(int i = 0; i<interpolate_image_min.width(); i++){
        for(int j=0; j<interpolate_image_min.height();j++){

            if(i==0){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }else if(j==0){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }else if(i==interpolate_image_min.width()-1){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }else if(j==interpolate_image_min.height()-1){
                interpolate_image_min(i,j) = median;
                interpolate_image_max(i,j) = median;
            }
        }
    }

    //Dim 0
    for(int i = 2; i<interpolate_image_min.width()-1; i=i+2){
        for(int j=2; j<interpolate_image_min.height()-1;j=j+2){
            type_pixels minInterval1 = std::min(interpolate_image_min(i-1,j),interpolate_image_min(i+1,j));
            type_pixels minInterval2 = std::min(interpolate_image_min(i,j-1),interpolate_image_min(i,j+1));
            interpolate_image_min(i,j) = std::min(minInterval1,minInterval2);

            type_pixels maxInterval1 = std::max(interpolate_image_max(i-1,j),interpolate_image_max(i+1,j));
            type_pixels maxInterval2 = std::max(interpolate_image_max(i,j-1),interpolate_image_max(i,j+1));
            interpolate_image_max(i,j) = std::min(maxInterval1,maxInterval2);
        }
    }
}

bool TreeOfShape::is_empty(std::map<int,std::queue<LibTIM::Point<LibTIM::TCoord>>>& q){
    bool result = true;
    for(auto it=q.begin();it!=q.end();++it)
        result = result && it->second.empty();
    return result;
}

void TreeOfShape::next_unempty(std::map<int,std::queue<LibTIM::Point<LibTIM::TCoord>>>& q,type_pixels& l){
    auto it = q.find(l);
    bool find_next = false;
    bool find_prev = false;
    int l_next,l_prev;
    if(is_empty(q))
        return;
    for(auto it_next=it;it_next!=q.end() && !find_next;++it_next){
        if(!it_next->second.empty()){
            find_next = true;
            l_next = it_next->first;
        }
    }
    for(auto it_prev=it;it_prev!=q.begin() && !find_prev;it_prev--){
        if(!it_prev->second.empty()){
            find_prev = true;
            l_prev = it_prev->first;
        }
    }
    if(!find_prev){
        it = q.begin();
        if(!it->second.empty()){
            find_prev = true;
            l_prev = it->first;
        }
    }

    if(!find_next){
        l=l_prev;
        return;
    }
    if(!find_prev){
        l=l_next;
        return;
    }
    if(abs(l-l_prev) > abs(l_next-l)){
        l=l_next;
    }else{
        l=l_prev;
    }
}

LibTIM::Point<LibTIM::TCoord> TreeOfShape::priority_pop(std::map<int,std::queue<LibTIM::Point<LibTIM::TCoord>>>& q,type_pixels& l){
    if(q[l].empty()){
        next_unempty(q,l);
    }
    LibTIM::Point<LibTIM::TCoord> result = q[l].front();
    q[l].pop();
    return result;
}

void TreeOfShape::priority_push(std::map<int,std::queue<LibTIM::Point<LibTIM::TCoord>>>& q,LibTIM::Point<LibTIM::TCoord> h,Image<type_pixels>& im_min,Image<type_pixels>& im_max,type_pixels& l){
    type_pixels lower = im_min(h.x,h.y);
    type_pixels upper = im_max(h.x,h.y);
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
    if(q.count(l2) == 0){
        q.insert(std::make_pair(l2,std::queue<LibTIM::Point<LibTIM::TCoord>>()));
    }
    q[l2].push(h);
}

std::vector<LibTIM::Point<LibTIM::TCoord>> TreeOfShape::get_voisinage(LibTIM::Point<LibTIM::TCoord>& p,Image<type_pixels>& im){
    std::vector<LibTIM::Point<LibTIM::TCoord>> result;

    for(int i=-1;i<=1;i++){
        if(i==0)
            continue;
        if(p.x+i >=0 && p.x+i < im.width())
            result.push_back(LibTIM::Point<LibTIM::TCoord>(p.x+i,p.y));
        if(p.y+i >=0 && p.y+i < im.height())
            result.push_back(LibTIM::Point<LibTIM::TCoord>(p.x,p.y+i));
    }
    return result;
}

void TreeOfShape::sort(Image<type_pixels>& result_img){
    result_img.resize(interpolate_image_max.width(),interpolate_image_max.height(),1,1);
    std::vector<std::vector<bool>> deja_vu;
    deja_vu.resize(interpolate_image_min.width());
    for(int i=0;i<interpolate_image_min.width();i++){
        deja_vu[i].resize(interpolate_image_min.height());
        for(int j=0;j<interpolate_image_min.height();j++){
            deja_vu[i][j] = false;
        }
    }
    std::map<int,std::queue<LibTIM::Point<LibTIM::TCoord>>> hierarchical_queue;

    hierarchical_queue.insert(std::make_pair(interpolate_image_max(0,0),std::queue<LibTIM::Point<LibTIM::TCoord>>()));
    hierarchical_queue[interpolate_image_max(0,0)].push(LibTIM::Point<LibTIM::TCoord>(0,0));
    deja_vu[0][0] = true;

    type_pixels l = interpolate_image_max(0,0);

    while(!is_empty(hierarchical_queue)){
        LibTIM::Point<LibTIM::TCoord> h = priority_pop(hierarchical_queue,l);
        result_img(h.x,h.y) = l;
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


LibTIM::Point<LibTIM::TCoord> TreeOfShape::find_root(std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>>& zpar,LibTIM::Point<LibTIM::TCoord>& x){
    LibTIM::Point<LibTIM::TCoord> p = zpar[x.x][x.y];
    if(p.x == x.x && p.y == x.y){
        return x;
    }
    zpar[x.x][x.y] = find_root(zpar,zpar[x.x][x.y]);
    return zpar[x.x][x.y];
}

std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> TreeOfShape::union_find(){
    std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> zpar;
    zpar.resize(interpolate_image_min.width());
    for(int i=0;i<interpolate_image_min.width();i++){
        zpar[i].resize(interpolate_image_min.height());
        for(int j=0;j<interpolate_image_min.height();j++){
            zpar[i][j] = LibTIM::Point<LibTIM::TCoord>(-1,-1);
        }
    }
    parent.resize(interpolate_image_min.width());
    for(int i=0;i<interpolate_image_min.width();i++){
        parent[i].resize(interpolate_image_min.height());
        for(int j=0;j<interpolate_image_min.height();j++){
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

void TreeOfShape::canonize_tree(Image<type_pixels>& f){
    for(unsigned i=0;i<R.size();i++){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
        if(f(parent[q.x][q.y].x,parent[q.x][q.y].y) == f(q.x,q.y)){
            parent[p.x][p.y] = parent[q.x][q.y];
        }
    }
}

bool TreeOfShape::is_in_image(LibTIM::Point<LibTIM::TCoord>& p){
    LibTIM::TCoord x = p.x,y=p.y;
    if(x == 1 || y == 1 || x == interpolate_image_max.width()-2 || y == interpolate_image_max.height()-2){
        return false;
    }
    x-=1;
    y-=1;
    return (x%4) == 0 && (y%4) == 0;
}

std::vector<LibTIM::Point<LibTIM::TCoord>> TreeOfShape::liste_fils(LibTIM::Point<LibTIM::TCoord>& p){
    std::vector<LibTIM::Point<LibTIM::TCoord>> result;

    for(int i=0;i<interpolate_image_min.width();i++){
        for(int j=0;j<interpolate_image_min.height();j++){
            LibTIM::Point<LibTIM::TCoord> q = parent[i][j];
            if(i == p.x && j == p.y)
                continue;
            if(q.x == p.x && q.y == p.y){
                result.push_back(LibTIM::Point<LibTIM::TCoord>(i,j));
            }
        }
    }

    return result;
}


void TreeOfShape::un_interpolate(Image<type_pixels> &f){
    for(unsigned i=0;i<R.size();i++){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        if(is_in_image(p)){
            LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
            if(!is_in_image(q) && f(p.x,p.y) == f(q.x,q.y)){
                LibTIM::Point<LibTIM::TCoord> tmp = parent[q.x][q.y];
                parent[p.x][p.y] = tmp;

                if(parent[q.x][q.y].x == q.x && parent[q.x][q.y].y == q.y && !is_in_image(parent[q.x][q.y]))
                    parent[p.x][p.y] = p;
                parent[q.x][q.y] = p;

                if(f(parent[tmp.x][tmp.y].x,parent[tmp.x][tmp.y].y) == f(tmp.x,tmp.y)){
                    parent[p.x][p.y] = parent[tmp.x][tmp.y];
                }

                /*std::vector<LibTIM::Point<LibTIM::TCoord>> freres = liste_fils(q);
                for(auto& f:freres){
                    parent[f.x][f.y] = p;
                }
                parent[p.x][p.y] = parent[q.x][q.y];
                if(parent[q.x][q.y].x == q.x && parent[q.x][q.y].y == q.y)
                    parent[p.x][p.y] = p;
                parent[q.x][q.y] = q;*/
            }

        }
    }

    canonize_tree(f);

    std::vector<std::vector<LibTIM::Point<LibTIM::TCoord>>> parent_clean;
    std::vector<LibTIM::Point<LibTIM::TCoord>> R_clean;

    parent_clean.resize(image.width());
    for(int i=0;i<image.width();i++){
        parent_clean[i].resize(image.height());
        for(int j=0;j<image.height();j++){
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
                file << "\"(" << parent[x][y].x << "," << parent[x][y].y << ") area : " << area[parent[x][y].x][parent[x][y].y] <<"\" -- \"(" << x << "," << y << ") area : "<< area[x][y] <<"\"" << std::endl;
            }
        }
        file << "}" << std::endl;
        file.close();
    }
}

void TreeOfShape::compute_area(Image<type_pixels> &f){
    area.resize(image.width());
    for(int i=0;i<image.width();i++){
        area[i].resize(image.height());
        for(int j=0;j<image.height();j++){
            area[i][j] = 1;
        }
    }

    for(int i=R.size()-1;i>=0;i--){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
        if(q.x != p.x || q.y != p.y)
            area[q.x][q.y] += area[p.x][p.y];
    }

    for(int i=R.size()-1;i>=0;i--){
        LibTIM::Point<LibTIM::TCoord> p = R[i];
        LibTIM::Point<LibTIM::TCoord> q = parent[p.x][p.y];
        LibTIM::Point<LibTIM::TCoord> tmp((p.x+1)*4+1,(p.y+1)*4+1);
        LibTIM::Point<LibTIM::TCoord> tmp2((q.x+1)*4+1,(q.y+1)*4+1);
        if(f(tmp.x,tmp.y) == f(tmp2.x,tmp2.y))
            area[p.x][p.y] = area[q.x][q.y];
    }
}


void TreeOfShape::removeShape(int seuil){

    Image<type_pixels> newImage = Image<type_pixels>(image.width(),image.height());

    for(int i=0;i<image.width();i++){
        for(int j=0;j<image.height();j++){
            if(area[i][j] < seuil){
                LibTIM::Point<LibTIM::TCoord> pix = LibTIM::Point<LibTIM::TCoord>(i,j);
                newImage(i,j) = couleurParent(pix,seuil);
            }else{
                newImage(i,j) = image(i,j);
            }
        }
    }

    newImage.save("../resultRemoveShape.pgm");
}

type_pixels TreeOfShape::couleurParent(LibTIM::Point<LibTIM::TCoord> &p, int seuil){

    LibTIM::Point<LibTIM::TCoord> pp = parent[p.x][p.y];

    if(pp.x == p.x && pp.y == p.y && area[pp.x][pp.y] < seuil ){
        return image(pp.x,pp.y);
    }else if( area[pp.x][pp.y] < seuil){
        return couleurParent(pp,seuil);
    }else{
        return image(pp.x,pp.y);
    }

}
