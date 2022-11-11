#include "pyramide.h"

Pyramide::Pyramide(const Vector &c, double co) : centre(c), cote(co) {}

Vector Pyramide::Vertex(int k) const {
    if (k==0) return Vector(-1,-1,-1);
    if (k==1) return Vector(1,-1,-1);
    if (k==2) return Vector(1,-1,1);
    if (k==3) return Vector(-1,-1,1);
}

Vector Pyramide::Center() const {
    return centre;
}




