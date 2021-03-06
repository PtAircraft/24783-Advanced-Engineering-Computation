#include <polygonalmesh.h>
#include <math.h>
#include "naca4digit.h"

std::vector <YsVec3> MakeNACA4DigitAirfoil(int naca,const double dz)
{
//    printf("check1.0\n");
    std::vector <YsVec3> vtx;
    std::vector <YsVec3> vtxl;
    // x cordinate
    double x = 0;
    //chord length
    double c = 1.0;
    double t,p,m;
    //obtain parameters;
    t = naca % 100;
    t = t/100;
    naca = naca / 100;
    p = naca % 10;
    p = p / 10;
    naca = naca / 10;
    m = double(naca) /100;
//    printf("t:%lf, p:%lf, m:%lf, dz:%lf\n",t,p,m,dz);
//    printf("check2.0\n");
    
    int size = 0;
    for (double z = 0; z < c; z = z + dz) {
        //calculate half thickness yt
        double yt = 5*t*(0.2969*sqrt(z/c) - 0.1260*(z/c) - 0.3516 * pow((z/c),2)
                         + 0.2843*pow((z/c),3) - 0.1015*pow((z/c),4));
        
        //calculate yc
        double yc;
        if (z >= 0 && z <= p*c) {
            yc = m/pow(p,2)*(2*p*(z/c)-pow((z/c),2));
        } else if (z <= c && z >= p*c) {
            yc = m/pow((1-p),2)*((1-2*p)+2*p*(z/c)-pow((z/c),2));
        }
        
        //calculate zu,zl,yu,yl
        double zu,zl,yu,yl;
        zu = z - yt;
        zl = z + yt;
        yu = yc + yt;
        yl = yc - yt;
        vtx.push_back(YsVec3(x,yu,zu));
        vtxl.push_back(YsVec3(x,yl,zl));
        size++;
//        printf("z:%lf, size: %d\n",z,size);
    }
    //calculate when z = c
    double z = c;
    double yt = 5*t*(0.2969*sqrt(z/c) - 0.1260*(z/c) - 0.3516 * pow((z/c),2)
                     + 0.2843*pow((z/c),3) - 0.1015*pow((z/c),4));
    double yc = m/pow((1-p),2)*((1-2*p)+2*p*(z/c)-pow((z/c),2));
    double zu,zl,yu,yl;
    zu = z - yt;
    zl = z + yt;
//    yu = yc + yt;
//    yl = yc - yt;
    yu = yl = 0;
    vtx.push_back(YsVec3(x,yu,zu));
    vtxl.push_back(YsVec3(x,yl,zl));
    size = size + 1;
    for (int i = size - 1; i >= 0; i--) {
        vtx.push_back(vtxl[i]);
    }
//    printf("size of vtx: %d\n",vtx.size());
	return vtx;
}

void MakeNACA4DigitAirfoilWing(class PolygonalMesh &mesh,int naca,float span,float sweepBack,float dihedral,float taper,float dz)
{
    //cross section at x = 0;
    std::vector <YsVec3> vtx;
    vtx = MakeNACA4DigitAirfoil(naca, dz);
    //cross section at x = -s;
    std::vector <YsVec3> vtx_s;
    for (int i = 0; i < vtx.size(); i++) {
        float a = vtx[i][0] * taper - span;
        float b = vtx[i][1] * taper + dihedral;
        float c = vtx[i][2] * taper + sweepBack;
        vtx_s.push_back(YsVec3(a,b,c));
//        printf("a: %f, b: %f, c: %f\n",a,b,c);
    }
    //cross section at x = s;
    std::vector <YsVec3> vtxs;
    for (int i = 0; i < vtx.size(); i++) {
        float a = vtx[i][0] * taper + span;
        float b = vtx[i][1] * taper + dihedral;
        float c = vtx[i][2] * taper + sweepBack;
        vtxs.push_back(YsVec3(a,b,c));
//        printf("a: %f, b: %f, c: %f\n",a,b,c);
    }
    
    int size = vtx.size();
    
    std::vector <PolygonalMesh::VertexHandle> vtHdArray0;
    std::vector <PolygonalMesh::VertexHandle> vtHdArrays;
    std::vector <PolygonalMesh::VertexHandle> vtHdArray_s;
    for (int i = 0; i < size; i++) {
        vtHdArray0.push_back(mesh.AddVertex(vtx[i]));
        vtHdArrays.push_back(mesh.AddVertex(vtxs[i]));
        vtHdArray_s.push_back(mesh.AddVertex(vtx_s[i]));
    }
    
    for (int i = 0; i < size; i++) {
        std::vector<PolygonalMesh::VertexHandle> plVtHd;
        //triangle
        plVtHd.push_back(vtHdArray0[i]);
        plVtHd.push_back(vtHdArray0[(i+1)%size]);
        plVtHd.push_back(vtHdArrays[i]);
        //norm
        YsVec3 v1 = vtx[i] - vtxs[i];
        YsVec3 v2 = vtx[(i+1)%size] - vtxs[i];
        YsVec3 crs1=YsUnitVector(v1^v2);
        //add to mesh s
        auto plHd = mesh.AddPolygon(plVtHd);
        mesh.SetPolygonNormal(plHd,crs1);
        //set color
        mesh.SetPolygonColor(plHd,YsBlue());
 
        //triangle
        std::vector<PolygonalMesh::VertexHandle> plVtHd1;
        plVtHd1.push_back(vtHdArrays[(i+1)%size]);
        plVtHd1.push_back(vtHdArrays[i]);
        plVtHd1.push_back(vtHdArray0[(i+1)%size]);
        //norm
        YsVec3 v3 = vtxs[i] - vtxs[(i+1)%size];
        YsVec3 v4 = vtx[(i+1)%size] - vtxs[i];
        YsVec3 crs2=YsUnitVector(v3^v4);
        //add to mesh s
        auto plHd1 = mesh.AddPolygon(plVtHd1);
        mesh.SetPolygonNormal(plHd1,crs1);
        //set color
        mesh.SetPolygonColor(plHd1,YsBlue());
        
        //triangle
        std::vector<PolygonalMesh::VertexHandle> plVtHd2;
        plVtHd2.push_back(vtHdArray0[(i+1)%size]);
        plVtHd2.push_back(vtHdArray0[i]);
        plVtHd2.push_back(vtHdArray_s[i]);
        //norm
        YsVec3 v5 = vtx[(i+1)%size] - vtx[i];
        YsVec3 v6 = vtx[(i+1)%size] - vtx_s[i];
        YsVec3 crs3=YsUnitVector(v5^v6);
        //add to mesh s
        auto plHd2 = mesh.AddPolygon(plVtHd2);
        mesh.SetPolygonNormal(plHd2,crs3);
        //set color
        mesh.SetPolygonColor(plHd2,YsBlue());
        
        //triangle
        std::vector<PolygonalMesh::VertexHandle> plVtHd3;
        
        plVtHd3.push_back(vtHdArray_s[i]);
        plVtHd3.push_back(vtHdArray_s[(i+1)%size]);
        plVtHd3.push_back(vtHdArray0[(i+1)%size]);
        //norm
        YsVec3 v7 = vtx_s[(i+1)%size] - vtxs[(i+1)%size];
        YsVec3 v8 = vtx[(i+1)%size] - vtx_s[i];
        YsVec3 crs4=YsUnitVector(v7^v8);
        //add to mesh s
        auto plHd3 = mesh.AddPolygon(plVtHd3);
        mesh.SetPolygonNormal(plHd3,crs3);
        //set color
        mesh.SetPolygonColor(plHd3,YsBlue());
    }
    
}
