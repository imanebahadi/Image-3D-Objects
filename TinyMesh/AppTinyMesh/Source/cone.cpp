#include "cone.h"

Cone::Cone(const Vector &c, double r, Vector &h) : centre(c), rayon(r), Peak(h) {}

Vector Cone::Vertex(int div, int i) const {
    float a = ((float(2.f) * M_PI) / div) * float(i);

     return Vector(rayon * cos(a),
                   0, rayon * sin(a));
}

Vector Cone::getCenter() const{
    return centre;
}

Vector Cone::getPeak() const{
    return Peak;
}

