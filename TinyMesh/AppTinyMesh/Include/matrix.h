// Matrix

#pragma once

#include <vector>
#include <iostream>

#include "mathematics.h"

class Matrix {

public:
    double tab[9];

public:
    Matrix();
    Matrix(double tab[9]);
    Matrix xRotationMatrix(double angle);
    Matrix yRotationMatrix(double angle);
    Matrix zRotationMatrix(double angle);
    Matrix Scale(Vector v);
    Vector operator*(Vector & vect)const;


};
