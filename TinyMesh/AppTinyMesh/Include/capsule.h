#ifndef CAPSULE_H
#define CAPSULE_H


#include "mathematics.h"
class capsule
{
public :
    int div_cercle=15;
public:
    capsule();
    int getdivCercle();

    Vector Vertex(int t,float alpha, float beta) const;


};


#endif // CAPSULE_H
