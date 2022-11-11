#include "capsule.h"

capsule::capsule()
{

}

int capsule::getdivCercle(){
    return div_cercle;
};

Vector capsule::Vertex(int i,float alpha, float beta) const{
    int haut =1, bas = -1;

    return Vector(cos(alpha) * cos(beta),
                  (i > (div_cercle-1)/2) ? haut + sin(alpha) : bas + sin(alpha),
                  cos(alpha) * sin(beta));
}
