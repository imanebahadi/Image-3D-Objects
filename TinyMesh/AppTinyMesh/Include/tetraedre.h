// tetraedre

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Tetraedre
{
public:
  Vector centre; //Vector => 3D; si centre est int : non car dans un envir 3D, 1 point peut etre n'importe où
  double rayon;


public:
  //! Empty.
  Tetraedre() {}
  Tetraedre(const Vector &c, double r);
  Vector Center() const;
  Vector Vertex(int k, int i) const;

  //! Empty.
  ~Tetraedre() {}
};
