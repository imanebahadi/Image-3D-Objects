#include "mesh.h"

/*!
\class Mesh mesh.h

\brief Core triangle mesh class.
*/



/*!
\brief Initialize the mesh to empty.
*/
Mesh::Mesh()
{
}

/*!
\brief Initialize the mesh from a list of vertices and a list of triangles.

Indices must have a size multiple of three (three for triangle vertices and three for triangle normals).

\param vertices List of geometry vertices.
\param indices List of indices wich represent the geometry triangles.
*/
Mesh::Mesh(const std::vector<Vector>& vertices, const std::vector<int>& indices) :vertices(vertices), varray(indices)
{
  normals.resize(vertices.size(), Vector::Z);
}

/*!
\brief Create the mesh.

\param vertices Array of vertices.
\param normals Array of normals.
\param va, na Array of vertex and normal indexes.
*/
Mesh::Mesh(const std::vector<Vector>& vertices, const std::vector<Vector>& normals, const std::vector<int>& va, const std::vector<int>& na) :vertices(vertices), normals(normals), varray(va), narray(na)
{
}

/*!
\brief Reserve memory for arrays.
\param nv,nn,nvi,nvn Number of vertices, normals, vertex indexes and vertex normals.
*/
void Mesh::Reserve(int nv, int nn, int nvi, int nvn)
{
  vertices.reserve(nv);
  normals.reserve(nn);
  varray.reserve(nvi);
  narray.reserve(nvn);
}

/*!
\brief Empty
*/
Mesh::~Mesh()
{
}

/*!
\brief Smooth the normals of the mesh.

This function weights the normals of the faces by their corresponding area.
\sa Triangle::AreaNormal()
*/
void Mesh::SmoothNormals()
{
  // Initialize 
  normals.resize(vertices.size(), Vector::Null);

  narray = varray;

  // Accumulate normals
  for (int i = 0; i < varray.size(); i += 3)
  {
    Vector tn = Triangle(vertices[varray.at(i)], vertices[varray.at(i + 1)], vertices[varray.at(i + 2)]).AreaNormal();
    normals[narray[i + 0]] += tn;
    normals[narray[i + 1]] += tn;
    normals[narray[i + 2]] += tn;
  }

  // Normalize 
  for (int i = 0; i < normals.size(); i++)
  {
    Normalize(normals[i]);
  }
}

/*!
\brief Add a smooth triangle to the geometry.
\param a, b, c Index of the vertices.
\param na, nb, nc Index of the normals.
*/
void Mesh::AddSmoothTriangle(int a, int na, int b, int nb, int c, int nc)
{
  varray.push_back(a);
  narray.push_back(na);
  varray.push_back(b);
  narray.push_back(nb);
  varray.push_back(c);
  narray.push_back(nc);
}

/*!
\brief Add a triangle to the geometry.
\param a, b, c Index of the vertices.
\param n Index of the normal.
*/
void Mesh::AddTriangle(int a, int b, int c, int n)
{
  varray.push_back(a);
  narray.push_back(n);
  varray.push_back(b);
  narray.push_back(n);
  varray.push_back(c);
  narray.push_back(n);
}

/*!
\brief Add a smmoth quadrangle to the geometry.

Creates two smooth triangles abc and acd.

\param a, b, c, d  Index of the vertices.
\param na, nb, nc, nd Index of the normal for all vertices.
*/
void Mesh::AddSmoothQuadrangle(int a, int na, int b, int nb, int c, int nc, int d, int nd)
{
  // First triangle
  AddSmoothTriangle(a, na, b, nb, c, nc);

  // Second triangle
  AddSmoothTriangle(a, na, c, nc, d, nd);
}

/*!
\brief Add a quadrangle to the geometry.

\param a, b, c, d  Index of the vertices and normals.
*/
void Mesh::AddQuadrangle(int a, int b, int c, int d)
{
  AddSmoothQuadrangle(a, a, b, b, c, c, d, d);
}

/*!
\brief Compute the bounding box of the object.
*/
Box Mesh::GetBox() const
{
  if (vertices.size() == 0)
  {
    return Box::Null;
  }
  return Box(vertices);
}

/*!
\brief Creates an axis aligned box.

The object has 8 vertices, 6 normals and 12 triangles.
\param box The box.
*/
Mesh::Mesh(const Box& box)
{
  // Vertices
  vertices.resize(8);

  for (int i = 0; i < 8; i++)
  {
    vertices[i] = box.Vertex(i);
  }

  // Normals
  normals.push_back(Vector(-1, 0, 0));
  normals.push_back(Vector(1, 0, 0));
  normals.push_back(Vector(0, -1, 0));
  normals.push_back(Vector(0, 1, 0));
  normals.push_back(Vector(0, 0, -1));
  normals.push_back(Vector(0, 0, 1));

  // Reserve space for the triangle array
  varray.reserve(12 * 3);
  narray.reserve(12 * 3);

  AddTriangle(0, 2, 1, 4);
  AddTriangle(1, 2, 3, 4);

  AddTriangle(4, 5, 6, 5);
  AddTriangle(5, 7, 6, 5);

  AddTriangle(0, 4, 2, 0);
  AddTriangle(4, 6, 2, 0);

  AddTriangle(1, 3, 5, 1);
  AddTriangle(3, 7, 5, 1);

  AddTriangle(0, 1, 5, 2);
  AddTriangle(0, 5, 4, 2);

  AddTriangle(3, 2, 7, 3);
  AddTriangle(6, 7, 2, 3);
}


Mesh::Mesh(const Disque& disque) //construit l'objet passé en param
{
    int div = 50;
    vertices.resize(div+1);
    vertices[div] = disque.Center();
    normals.push_back(Vector(0,1,0));

    for(int i = 0; i < div; i++) vertices[i] = disque.Vertex(i, div);

    varray.reserve(6 * 3);
    narray.reserve(6 * 3);

    for(int i = 0; i < div; i++) AddTriangle(i, div, (i+1)%div, 0);
}

Mesh::Mesh(const Cylindre &cylindre) {
     int div = 100;
     vertices.resize(2*div + 2);
     int somme_haut = 2*div;
     int sommet_bas = 2*div+1;

     vertices[somme_haut] = cylindre.CentreHaut();
     vertices[sommet_bas] = cylindre.CentreBas();

     normals.push_back(cylindre.CentreHaut());
     normals.push_back(cylindre.CentreBas());

     for(int i = 0; i<2*div; i++) {
         vertices[i] = cylindre.Vertex(i, div);
         normals.push_back(cylindre.Normal(i, div));
     }

     varray.reserve(4*div * 3);
     narray.reserve(4*div *3);

     for(int i = 0; i<div; i++) {
         AddTriangle(sommet_bas, i, (i+1)%div, 1);
         AddTriangle(i, i+div, (i+1)%div, i%div);
         AddTriangle(somme_haut, i+div, (i+1)%div + div, 0);
         AddTriangle((i+1)%div, (i+1)%div + div, i + div, (i)%div);
     }
}

Mesh::Mesh(const tore& Tore)
{
    float beta, alpha;
    int cercleCrt, cercleSvt;
    int divCercle = 20;
    int R=4;

    vertices.resize(divCercle * divCercle);
    normals.resize(divCercle * divCercle);

    varray.reserve(divCercle * divCercle * 3);
    narray.reserve(divCercle * divCercle * 3);

    for(int i=0; i< divCercle; ++i){
        alpha = float(i) * (2.f) * M_PI / (divCercle - 1);

        for (int j=0; j<divCercle; ++j){
        beta = float(j) * (2.f) * M_PI / (divCercle - 1);

        normals [j + i * divCercle] = Vector((R + cos(beta)) * cos(alpha), sin(beta), (R + cos(beta)) * sin(alpha)) ;
        vertices[j + i * divCercle] = Vector((R + cos(beta)) * cos(alpha), sin(beta), (R + cos(beta)) * sin(alpha)) ;
        }
    }

    for (int i=0; i<divCercle - 1; ++i){

        cercleCrt = i*divCercle;
        cercleSvt = (i+1) * divCercle;

        for (int j=0; j<divCercle; ++j){
            AddSmoothTriangle(j+cercleCrt,j+cercleCrt,j+cercleSvt,j+cercleSvt,(j+1)%divCercle + cercleCrt,(j+1)%divCercle + cercleCrt);
            AddSmoothTriangle(j+cercleSvt,j+cercleSvt,(j+1)%divCercle + cercleCrt,(j+1)%divCercle + cercleCrt,(j+1)%divCercle + cercleSvt,(j+1)%divCercle + cercleSvt);
        }
    }
}



Mesh::Mesh(const capsule& capsule)
{
    float alpha, beta, disque_svt, disque_crt;
    int div_beta = 16;
    int div_alpha = capsule.div_cercle;
    vertices.resize(div_beta * div_alpha);
    normals.resize(div_beta * div_alpha);

    varray.reserve(div_beta * div_alpha * 3);
    narray.reserve(div_beta * div_alpha * 3);

    for(int i=0; i< div_alpha; ++i){

        alpha = (-0.5f) * M_PI + float(i) * M_PI / (div_alpha-1);

        for (int j=0; j< div_beta; ++j){
            beta = float(j) * (  (2.f) * M_PI / (div_beta) );
            normals[j + i * div_beta] = capsule.Vertex(i,alpha, beta);
            vertices[j + i * div_beta] = capsule.Vertex(i,alpha, beta);
        }
    }

    for(int i=0; i<div_alpha - 1; ++i){
        disque_crt= i * div_beta;
        disque_svt = (i+1) * div_beta;

        for (int j=0; j<div_beta; ++j){
            AddSmoothTriangle(j+disque_crt,j+disque_crt,j+disque_svt,j+disque_svt,(j+1)%div_beta + disque_crt,(j+1)%div_beta + disque_crt );
            AddSmoothTriangle(j+disque_svt,j+disque_svt,(j+1)%div_beta + disque_svt,(j+1)%div_beta + disque_svt,(j+1)%div_beta + disque_crt,(j+1)%div_beta + disque_crt);
        }
    }
}




 Mesh::Mesh(const Sphere& sphere)
 {
    float alpha, beta, disque_svt, disque_crt;

    int div_beta = sphere.getDisqueTr();
    int div_alpha = sphere.getNbDisque();

    vertices.resize(div_beta * div_alpha);
    normals.resize(div_beta * div_alpha);

    varray.reserve(div_beta * div_alpha * 3);
    narray.reserve(div_beta * div_alpha * 3);

    for(int i=0; i< div_alpha; ++i){

        alpha = (-0.5f) * M_PI + float(i) * M_PI / (div_alpha-1);

        for (int j=0; j< div_beta; ++j){
            beta = float(j) * (  (2.f) * M_PI / (div_beta) );

            normals[j + i * div_beta] = sphere.Vertex(alpha, beta);
            vertices[j + i * div_beta] = sphere.Vertex(alpha, beta);

         }
      }

    for(int i=0; i<div_alpha - 1; ++i){

        disque_crt= i * div_beta;
        disque_svt = (i+1) * div_beta;

        for (int j=0; j<div_beta; ++j){

            AddSmoothTriangle(j+disque_crt,j+disque_crt,j+disque_svt,j+disque_svt,(j+1)%div_beta + disque_crt,(j+1)%div_beta + disque_crt );
            AddSmoothTriangle(j+disque_svt,j+disque_svt,(j+1)%div_beta + disque_svt,(j+1)%div_beta + disque_svt,(j+1)%div_beta + disque_crt,(j+1)%div_beta + disque_crt);
        }
    }
};

 Mesh::Mesh(const Tetraedre& tetraedre)
 {
     vertices.resize(4);

     vertices[0] = Vector(1,1,1);
     vertices[1] = Vector(1,-1,-1);
     vertices[2] = Vector(-1,1,-1);
     vertices[3] = Vector(-1,-1,1);


     normals.push_back(Vector(4,-4,-4));
     normals.push_back(Vector(-4,-4,-4));
     normals.push_back(Vector(4,4,-4));
     normals.push_back(Vector(-4,-4,4));

     varray.reserve(4 * 3 );
     narray.reserve(4 * 3);

     AddTriangle(0,2,1,0);
     AddTriangle(1,2,3,1);
     AddTriangle(3,2,0,2);
     AddTriangle(0,3,1,3);

 };

 Mesh::Mesh(const Cone& cone)
 {
    int div = 50;

    narray.reserve((div+1)*3);
    varray.reserve((div+1)*3);
    vertices.resize(div+2);

    normals.push_back(Vector(0,1,0));

    vertices[div] = cone.getCenter();
    vertices[div] = cone.getPeak();

    for(int i=0; i<div; ++i) vertices[i]= cone.Vertex(div,i);

    for(int i=0; i< div; ++i){
        AddTriangle(i,div,(i+1)%div,0);
        AddTriangle(i,div+1,(i+1)%div,0);
    }
 }


 Mesh::Mesh(const Pyramide& pyra)
 {
     int div = 4;
     vertices.resize(div+2);
     vertices[div] = Vector(0,1,0);


     normals.push_back(Vector(0,-1,0));
     normals.push_back(Vector(4,-4,-4));
     normals.push_back(Vector(-4,-4,-4));
     normals.push_back(Vector(4,4,-4));
     normals.push_back(Vector(-4,-4,4));


     for(int i = 0; i < 4; i++) vertices[i] = pyra.Vertex(i);

     varray.reserve(6 * 3);
     narray.reserve(6 * 3);

     AddTriangle(0, 1, 3, 4);
     AddTriangle(3, 1, 2, 4);

     for(int i = 0; i < div; i++) AddTriangle(i, div, (i+1)%div, 0);
}


// transformations géometriques

 void Mesh::RotateX(double alpha) {
     Matrix m;
     double AngleRadians = Math::DegreeToRadian(alpha);
     Matrix res = m.xRotationMatrix(AngleRadians);

     for (int i =0; i < vertices.size(); i++) vertices[i] = res * vertices[i];
 }

 void Mesh::RotateY(double alpha) {
     Matrix m;
     double AngleRadians = Math::DegreeToRadian(alpha);
     Matrix res = m.yRotationMatrix(AngleRadians);

     for (int i =0; i < vertices.size(); i++) vertices[i] = res * vertices[i];
 }

 void Mesh::RotateZ(double alpha) {
     Matrix m;
     double AngleRadians = Math::DegreeToRadian(alpha);
     Matrix res = m.zRotationMatrix(AngleRadians);

     for (int i =0; i < vertices.size(); i++) vertices[i] = res * vertices[i];
 }

 void Mesh::Translate(Vector v){
     for (int i = 0; i < vertices.size(); i++)
     {
         vertices[i] += v;
     }
 }

 void Mesh::Scale(Vector v) {
     Matrix m;
     Matrix res = m.Scale(v);

     vertices.resize(5000);

     for (int i =0; i < vertices.size(); i++) vertices[i] = res * vertices[i];
 }


void Mesh::Merge(const Mesh & mesh)
{
   int varraySize = mesh.varray.size();
   int narraySize = mesh.narray.size();
   int verticesSize = this->vertices.size();
   int normalsSize = this->normals.size();

   for(int i = 0; i < varraySize; i++) this->varray.push_back(mesh.varray.at(i) + verticesSize );

   for(int i = 0; i < narraySize; i++) this->narray.push_back(mesh.narray.at(i) + normalsSize) ;

   for(int i = 0; i < mesh.vertices.size(); i++) this->vertices.push_back(mesh.vertices.at(i));

   for(int i = 0; i < mesh.normals.size(); i++) this->normals.push_back(mesh.normals.at(i));

}








/*!
\brief Scale the mesh.
\param s Scaling factor.
*/
void Mesh::Scale(double s)
{
    // Vertexes
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] *= s;
    }

    if (s < 0.0)
    {
        // Normals
        for (int i = 0; i < normals.size(); i++)
        {
            normals[i] = -normals[i];
        }
    }
}



#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegularExpression>
#include <QtCore/qstring.h>

/*!
\brief Import a mesh from an .obj file.
\param filename File name.
*/
void Mesh::Load(const QString& filename)
{
  vertices.clear();
  normals.clear();
  varray.clear();
  narray.clear();

  QFile data(filename);

  if (!data.open(QFile::ReadOnly))
    return;
  QTextStream in(&data);

  // Set of regular expressions : Vertex, Normal, Triangle
  QRegularExpression rexv("v\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)");
  QRegularExpression rexn("vn\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)\\s*([-|+|\\s]\\d*\\.\\d+)");
  QRegularExpression rext("f\\s*(\\d*)/\\d*/(\\d*)\\s*(\\d*)/\\d*/(\\d*)\\s*(\\d*)/\\d*/(\\d*)");
  while (!in.atEnd())
  {
    QString line = in.readLine();
    QRegularExpressionMatch match = rexv.match(line);
    QRegularExpressionMatch matchN = rexn.match(line);
    QRegularExpressionMatch matchT = rext.match(line);
    if (match.hasMatch())//rexv.indexIn(line, 0) > -1)
    {
      Vector q = Vector(match.captured(1).toDouble(), match.captured(2).toDouble(), match.captured(3).toDouble()); vertices.push_back(q);
    }
    else if (matchN.hasMatch())//rexn.indexIn(line, 0) > -1)
    {
      Vector q = Vector(matchN.captured(1).toDouble(), matchN.captured(2).toDouble(), matchN.captured(3).toDouble());  normals.push_back(q);
    }
    else if (matchT.hasMatch())//rext.indexIn(line, 0) > -1)
    {
      varray.push_back(matchT.captured(1).toInt() - 1);
      varray.push_back(matchT.captured(3).toInt() - 1);
      varray.push_back(matchT.captured(5).toInt() - 1);
      narray.push_back(matchT.captured(2).toInt() - 1);
      narray.push_back(matchT.captured(4).toInt() - 1);
      narray.push_back(matchT.captured(6).toInt() - 1);
    }
  }
  data.close();
}

/*!
\brief Save the mesh in .obj format, with vertices and normals.
\param url Filename.
\param meshName %Mesh name in .obj file.
*/
void Mesh::SaveObj(const QString& url, const QString& meshName) const
{
  QFile data(url);
  if (!data.open(QFile::WriteOnly))
    return;
  QTextStream out(&data);
  out << "g " << meshName << Qt::endl;
  for (int i = 0; i < vertices.size(); i++)
    out << "v " << vertices.at(i)[0] << " " << vertices.at(i)[1] << " " << vertices.at(i)[2] << QString('\n');
  for (int i = 0; i < normals.size(); i++)
    out << "vn " << normals.at(i)[0] << " " << normals.at(i)[1] << " " << normals.at(i)[2] << QString('\n');
  for (int i = 0; i < varray.size(); i += 3)
  {
    out << "f " << varray.at(i) + 1 << "//" << narray.at(i) + 1 << " "
      << varray.at(i + 1) + 1 << "//" << narray.at(i + 1) + 1 << " "
      << varray.at(i + 2) + 1 << "//" << narray.at(i + 2) + 1 << " "
      << "\n";
  }
  out.flush();
  data.close();
}

