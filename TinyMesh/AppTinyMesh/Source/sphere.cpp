#include "sphere.h"

Sphere::Sphere(const Vector &c, double r, int DTr, int NbD) : centre(c), rayon(r), disqueTr(DTr), disqueNb(NbD) {}


Vector Sphere::Vertex(float alpha, float beta) const {
    return Vector(rayon * cos(alpha) * cos(beta), rayon * sin(alpha),rayon * cos(alpha) * sin(beta));
}

int Sphere::getDisqueTr() const{
    return disqueTr ;
}

int Sphere::getNbDisque() const{
    return disqueNb;
}

Vector Sphere::Center() const {
    return centre;
}




