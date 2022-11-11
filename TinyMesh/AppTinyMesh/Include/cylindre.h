#ifndef CYLINDRE_H
#define CYLINDRE_H

#include "mathematics.h"

class Cylindre {
protected:
    Vector centre;
    double hauteur;
    double rayon;

public:
    Cylindre(const Vector&, double, double);
    Vector Vertex(int, int) const;
    Vector Normal(int, int) const;
    Vector CentreHaut() const;
    Vector CentreBas() const;

};

#endif // CYLINDRE_H
