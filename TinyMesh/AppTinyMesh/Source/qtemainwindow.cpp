#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"
#include <QString>

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->sphereMesh, SIGNAL(clicked()), this, SLOT(SphereMeshExample()));
    connect(uiw->cylindreMesh, SIGNAL(clicked()), this, SLOT(cylindreMeshExample()));
    connect(uiw->toreMesh, SIGNAL(clicked()), this, SLOT(ToreMeshExample()));
    connect(uiw->capsuleMesh, SIGNAL(clicked()), this, SLOT(capsuleMeshExample()));
    connect(uiw->tetraedreMesh, SIGNAL(clicked()), this, SLOT(TetraedreMeshExample()));
    connect(uiw->tetraedreMesh, SIGNAL(clicked()), this, SLOT(TetraedreMeshExample()));
    connect(uiw->coneMesh, SIGNAL(clicked()), this, SLOT(coneMeshExample()));
    connect(uiw->pyramidMesh, SIGNAL(clicked()), this, SLOT(PyramideMeshExample()));
    connect(uiw->disqueMesh, SIGNAL(clicked()), this, SLOT(DisqueMeshExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
    Mesh boxMesh = Mesh(Box(1.0));

    //boxMesh.RotateX(45);
    //boxMesh.RotateY(45);
    //boxMesh.RotateZ(45);
    //boxMesh.Scale(Vector(12,25,15));
    //boxMesh.Translate(Vector(12,25,15));
    Mesh CapsuleMesh = Mesh(capsule());

    boxMesh.Merge(CapsuleMesh);

	std::vector<Color> cols;
	cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
  AnalyticScalarField implicit;

  Mesh implicitMesh;
  implicit.Polygonize(31, implicitMesh, Box(2.0));

  std::vector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::cylindreMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Mesh cyl = Mesh(Cylindre(Vector(0,0,0), 3, 5));

    std::vector<Color> cols;
    cols.resize(cyl.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(cyl, cols, cyl.VertexIndexes());
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time cylindre "<<timer << std::endl;
    UpdateGeometry();
}

void MainWindow::coneMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Vector Centre = Vector(0,0,0);
    Vector Peak = Vector(0,4,0);
    double Rayon = 2;


    Mesh coneMesh = Mesh(Cone(Centre,Rayon,Peak));

    std::vector<Color> cols;
    cols.resize(coneMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(coneMesh, cols, coneMesh.VertexIndexes());
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time cone "<<timer << std::endl;
    UpdateGeometry();
}


void MainWindow::capsuleMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Vector vect;

    Mesh CapsuleMesh = Mesh(capsule());

    std::vector<Color> cols;
    cols.resize(CapsuleMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);



    meshColor = MeshColor(CapsuleMesh, cols, CapsuleMesh.VertexIndexes());

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time capsule "<<timer << std::endl;
    UpdateGeometry();
}

void MainWindow::TetraedreMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Vector vect;

    Mesh TetraedreMesh = Mesh(Tetraedre());
    TetraedreMesh.Scale(Vector(2,5,2));

    std::vector<Color> cols;
    cols.resize(TetraedreMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(TetraedreMesh, cols, TetraedreMesh.VertexIndexes());
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time tetraedre "<<timer << std::endl;
    UpdateGeometry();
}



void MainWindow::SphereMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Vector Centre = Vector(0,0,0);
    int Rayon = 2;
    int DisquesTriangles = 40;
    int NombresDisques = 15;

    Mesh SphereMesh = Mesh(Sphere(Centre,Rayon,DisquesTriangles,NombresDisques));

    std::vector<Color> cols;
    cols.resize(SphereMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(SphereMesh, cols, SphereMesh.VertexIndexes());
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time sphere "<<timer << std::endl;
    UpdateGeometry();
}


void MainWindow::ToreMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Vector vect;


    Mesh ToreMesh = Mesh(tore());

    std::vector<Color> cols;
    cols.resize(ToreMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(ToreMesh, cols, ToreMesh.VertexIndexes());

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time tore "<<timer << std::endl;
    UpdateGeometry();
}


void MainWindow::DisqueMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Vector vect;
    Mesh DisqueMesh = Mesh(Disque(vect, 1.0));

    std::vector<Color> cols;
    cols.resize(DisqueMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(DisqueMesh, cols, DisqueMesh.VertexIndexes());
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time disque "<<timer << std::endl;
    UpdateGeometry();
}

void MainWindow::PyramideMeshExample()
{
    auto start = std::chrono::high_resolution_clock::now();
    Mesh PyramideMesh = Mesh(Pyramide());
    Mesh ToreMesh = Mesh(tore());



    std::vector<Color> cols;
    cols.resize(PyramideMesh.Vertexes());
    for (int i = 0; i < cols.size(); i++)
    cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(PyramideMesh, cols, PyramideMesh.VertexIndexes());

    PyramideMesh.RotateX(45);

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    long long timer = (end - start).count() ; // Get the elapse time in milliseconds
    std::cout<<"time pyramide "<<timer << std::endl;

    UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}

