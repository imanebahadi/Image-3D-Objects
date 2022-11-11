#include "cylindre.h"

Cylindre::Cylindre(const Vector &c, double r, double h) : centre(c), rayon(r), hauteur(h) {}


Vector Cylindre::Vertex(int i, int div) const {
    double a = ((2 * M_PI) / div) *i;

    double centre1;

    if(i < div) centre1 = centre[1] - (hauteur/2);
    else centre1 = centre[1] + (hauteur/2);

    return Vector(rayon * cos(a) + centre[0], rayon * sin(a) + centre[1], centre1 + centre[2]);
}

Vector Cylindre::Normal(int i, int div) const {
    double a = ((2 * M_PI) / i) *i;

     return Vector(rayon * cos(a) + centre[0], 0, rayon * cos(a) + centre[2]);
}

Vector Cylindre::CentreHaut() const {
    return Vector(centre[0], centre[1] + (hauteur/2), centre[2]);
}

Vector Cylindre::CentreBas() const {
    return Vector(centre[0], centre[1] - (hauteur/2), centre[2]);
}





