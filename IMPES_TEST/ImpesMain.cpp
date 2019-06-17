//$Id: main.cc,v 1.21 2010-07-22 17:43:43 caju Exp $
#ifdef HAVE_CONFIG_H
#include <pz_config.h>
#endif

#include "pzgeoel.h"
#include "pzgnode.h"
#include "pzgmesh.h"
#include "pzbiharmonic.h"
#include "pzcmesh.h"
#include "pzintel.h"
#include "pzcompel.h"

#include "pzfmatrix.h"
#include "pzvec.h"
#include "pzmanvector.h"
#include "pzstack.h"

#include "pzanalysis.h"
#include "pzfstrmatrix.h"
#include "pzskylstrmatrix.h"
#include "pzstepsolver.h"
#include "pzgeopyramid.h"
#include "TPZGeoLinear.h"

#include <TPZRefPattern.h>

#include "TPZMaterial.h"
#include "pzelasmat.h"
#include "pzlog.h"

#include "pzgengrid.h"

#include <time.h>
#include <stdio.h>

#include <math.h>

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

#include <set>
#include <map>
#include <vector>
#include "TPZRefPatternDataBase.h"
#include "TPZRefPatternTools.h"
#include "TPZVTKGeoMesh.h"
#include "TPZExtendGridDimension.h"




#include "TPZMatLaplacian.h"
#include "pzpoisson3d.h"
#include "mixedpoisson.h"
#include "pzbndcond.h"
#include "TPZSSpStructMatrix.h"
#include "pzskylstrmatrix.h"
#include "TPZSkylineNSymStructMatrix.h"
#include "TPZHybridizeHDiv.h"
#include "pzbuildmultiphysicsmesh.h"
#include "TPZGmshReader.h"
#include "TPZMixedDarcyFlow.h"
#include "pzfmatrix.h"
#include "pzskylstrmatrix.h"

TPZCompMesh *GenerateCompMesh(TPZGeoMesh *gmesh);

using namespace std;

int main(){

    //Leer la malla de gmsh
TPZGmshReader read;
read.SetFormatVersion("3");
TPZGeoMesh *gmesh;
// crea malla geometrica
gmesh = read.GeometricGmshMesh("malla1.msh");
std::ofstream archivo("malla_comp.vtk");
TPZVTKGeoMesh::PrintGMeshVTK(gmesh, archivo);

//crea malla computacional
TPZCompMesh *cmesh = GenerateCompMesh(gmesh);
TPZVTKGeoMesh::PrintCMeshVTK(cmesh,archivo);

//crear analysis 
TPZAnalysis *an = new TPZAnalysis(cmesh, true);
std::cout<<"OK"<<std::endl;
TPZSkylineStructMatrix matrix(cmesh);
matrix.SetNumThreads(4);
TPZStepSolver<STATE> step;
step.SetDirect(ECholesky);
an->SetSolver(step);

an->SetStructuralMatrix(matrix);

an->Solve();

return 0;
}

TPZCompMesh *GenerateCompMesh(TPZGeoMesh *gmesh){
    TPZCompMesh *cmesh = new TPZCompMesh(gmesh);
    TPZMixedDarcyFlow *material = new TPZMixedDarcyFlow(4,2);
    material->SetPermeability(10);
    cmesh->InsertMaterialObject(material);
    //D =0
    //N =2
    int dimension=2;
    TPZFMatrix<STATE> val1(dimension,dimension,0.0), val2(dimension,1,0.0);
    val2(0,0)=100;
    TPZMaterial *bc_inlet = material->CreateBC(material,1,0,val1,val2);
    cmesh->InsertMaterialObject(bc_inlet);
    val2(0,0)=0;
    TPZMaterial *bc_outlet = material->CreateBC(material,2,0,val1,val2);
    cmesh->InsertMaterialObject(bc_outlet);
    
    val2(0,0)=0;
    TPZMaterial *bc_impervious = material->CreateBC(material,3,1,val1,val2);
    cmesh->InsertMaterialObject(bc_impervious);
    
    cmesh->SetAllCreateFunctionsContinuous();
    cmesh->SetDefaultOrder(1);

    cmesh->AutoBuild();


}
