#include "tetraedre.h"

Tetraedre::Tetraedre(const Vector &c, double r) : centre(c), rayon(r) {}

Vector Tetraedre::Center() const {
    return centre;
}

