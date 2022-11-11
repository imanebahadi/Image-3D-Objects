#include "disque.h"

Disque::Disque(const Vector &c, double r) : centre(c), rayon(r) {}

Vector Disque::Vertex(int i, int div) const {
    double a = ((2 * M_PI) / div) *i;

    return Vector(rayon * cos(a) + centre[0], rayon * sin(a) + centre[1], centre[2]);
}


Vector Disque::Center() const {
    return centre;
}



