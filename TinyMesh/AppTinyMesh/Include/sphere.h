// Sphere

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Sphere
{
public:
  Vector centre; //Vector => 3D; si centre est int : non car dans un envir 3D, 1 point peut etre n'importe où
  double rayon;
  int disqueTr;
  int disqueNb;


public:
  //! Empty.
  Sphere() {}
  Sphere(const Vector &c, double r, int DTr, int NbD);
  Vector Center() const;
  Vector Vertex(float alpha, float beta) const;
  int getDisqueTr() const;
  int getNbDisque() const;



  //! Empty.
  ~Sphere() {}



};




