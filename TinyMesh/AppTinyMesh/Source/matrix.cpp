 // Matrix

#include "matrix.h"


Matrix::Matrix(double tab1[9]) {
    for (int i=0; i<9; i++) {
        tab[i] = tab1[i];
    }
}

Matrix:: Matrix() {}

Matrix Matrix::xRotationMatrix(double alpha){ //rotation sur les X
    double tab[9] = {1,0,0,
                     0, cos(alpha), -sin(alpha),
                     0, sin(alpha), cos(alpha)};
    return Matrix(tab);
}

Matrix Matrix::yRotationMatrix(double alpha){ //rotation sur les Y
    double tab[9] = {cos(alpha),0,sin(alpha),
                     0, 1, 0,
                     -sin(alpha), 0, cos(alpha)};
    return Matrix(tab);
}

Matrix Matrix::zRotationMatrix(double alpha){ //rotation sur les Z
    double tab[9] = {cos(alpha),-sin(alpha),0,
                     sin(alpha), cos(alpha), 0,
                     0, 0, 1};
    return Matrix(tab);
}

Matrix Matrix::Scale(Vector v){ //rotation sur les X
    double tab[9] = {v[0],0,0,
                     0, v[1], 0,
                     0, 0, v[2]};
    return Matrix(tab);
}

Vector Matrix::operator*(Vector & vect) const{
    Vector S = Vector(0);
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            S[i] += vect[j] * tab[3*i+j];
        }
    }
    return S;
}

