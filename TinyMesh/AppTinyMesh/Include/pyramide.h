// Pyramide

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Pyramide
{
public:
  Vector centre; //Vector => 3D; si centre est int : non car dans un envir 3D, 1 point peut etre n'importe où
  double cote;


public:
  //! Empty.
  Pyramide() {}
  Pyramide(const Vector &c, double co);
  Vector Center() const;
  Vector Vertex(int k) const;

  //! Empty.
  ~Pyramide() {}



};




