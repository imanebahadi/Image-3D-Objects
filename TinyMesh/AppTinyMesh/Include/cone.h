// Cone

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Cone
{
public:
  Vector centre; //Vector => 3D; si centre est int : non car dans un envir 3D, 1 point peut etre n'importe où
  Vector Peak;
  double rayon;


public:
  //! Empty.
  Cone() {}
  Cone(const Vector &c, double r, Vector &h);
  Vector getCenter() const;
  Vector getPeak() const;
  Vector Vertex(int k, int i) const;
  Vector Normal(int k, int precision) const;


  //! Empty.
  ~Cone() {}



};




