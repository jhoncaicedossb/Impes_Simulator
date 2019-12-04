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
TPZCompMesh *TransportMesh(TPZGeoMesh *gmesh);

using namespace std;

int main(){
 
    //Leer la malla de gmsh
TPZGmshReader read;
read.SetFormatVersion("4.1");
    
TPZGeoMesh *gmesh;
// crea malla geometrica
gmesh = read.GeometricGmshMesh("caseiii.msh"); //nombre del archivo a leer
    gmesh->BuildConnectivity();
std::ofstream archivo("malla_comp.vtk");
//TPZVTKGeoMesh::PrintGMeshVTK(gmesh, archivo);

//crea malla computacional
TPZCompMesh *cmesh = GenerateCompMesh(gmesh);
TPZVTKGeoMesh::PrintCMeshVTK(cmesh,archivo);

    
 
//crear analysis 

    TPZAnalysis *an = new TPZAnalysis(cmesh, true);
  std::cout<<"pase"<<std::endl;
    TPZSkylineStructMatrix matrix(cmesh);
    //        TPZSkylineStructMatrix matrix(cmesh);
    matrix.SetNumThreads(4);
    an->SetStructuralMatrix(matrix);
    TPZStepSolver<STATE> step;
    step.SetDirect(ELDLt);
    an->SetSolver(step);
    
    
    
//    TPZStepSolver<STATE> step;
//    step.SetDirect(ECholesky);
//    an->SetSolver(step);
    
//ensamblaje
    an->Assemble();
    
//solucion
an->Solve();
    
    
//posprocesamiento
    TPZStack<std::string,10> scalnames, vecnames;
    vecnames.Push("Flux");
    scalnames.Push("Pressure");
    //  scalnames.Push("Permeability");
    
    int div = 0;
    int dim=gmesh->Dimension();
    std::string fileresult("TestCaicedo.vtk");
    an->DefineGraphMesh(dim,scalnames,vecnames,fileresult);
    an->PostProcess(div,dim);

return 0;
}

TPZCompMesh *GenerateCompMesh(TPZGeoMesh *gmesh){
    TPZCompMesh *cmesh = new TPZCompMesh(gmesh);
    
    TPZMixedDarcyFlow *material = new TPZMixedDarcyFlow(4,2);
    material->SetPermeability(10);
    cmesh->InsertMaterialObject(material);
    int D =0;
    int N =1;
    int dimension=2;
    TPZFMatrix<STATE> val1(dimension,dimension,0.0), val2(dimension,N,0.0);
    val2(0,0)=100;
    TPZMaterial *bc_inlet = material->CreateBC(material,1,D,val1,val2);
    cmesh->InsertMaterialObject(bc_inlet);
    val2(0,0)=0;
    TPZMaterial *bc_outlet = material->CreateBC(material,2,D,val1,val2);
    cmesh->InsertMaterialObject(bc_outlet);
    
    val2(0,0)=0;
    TPZMaterial *bc_impervious = material->CreateBC(material,3,N,val1,val2);
    cmesh->InsertMaterialObject(bc_impervious);
   
    cmesh->SetAllCreateFunctionsContinuous();
    cmesh->SetDefaultOrder(1);

    cmesh->AutoBuild();
    int nel = cmesh->NElements();
    std::cout<<"nels ="<<nel<<std::endl;
    cmesh->InitializeBlock();
   
    return cmesh;
    
}
TPZCompMesh *TransportMesh(TPZGeoMesh *gmesh){
    
    TPZCompMesh *scmesh = new TPZCompMesh(gmesh);
    
    
    
    
}
