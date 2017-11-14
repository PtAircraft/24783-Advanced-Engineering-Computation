#include <fssimplewindow.h> // For FsSubSecondTimer
#include <meshlattice.h>

#include <vector>
#include <unordered_set>

#include <fslazywindow.h>


#include "glutil.h"

#include "ps6lib.h"

#include <math.h>

std::vector <float> MakeSliceVertexArray(const YsShellExt &mesh)
{
	auto t0=FsSubSecondTimer();
	std::vector <float> sliceVtx;
    YsVec3 min, max;
    mesh.GetBoundingBox(min,max);
    int flag = 1;
    
    auto ymax = max[1];
    auto ymin = min[1];
    double dy = (ymax - ymin) / 100;
    
    for (auto plHd = mesh.NullPolygon();true == mesh.MoveToNextPolygon(plHd);) {
        auto vtx = mesh.GetPolygonVertex(plHd);
        auto vp0 = mesh.GetVertexPosition(vtx[0]);
        auto vp1 = mesh.GetVertexPosition(vtx[1]);
        auto vp2 = mesh.GetVertexPosition(vtx[2]);
        

        // sorting vertex
        YsVec3 vpmax, vpmid,vpmin;
        if(vp0[1] == vp1[1] == vp2[1]) {
            continue;
        }
       
        if (vp0[1] == vp1[1]) {
            if (vp0[1] > vp2[1]) {
                vpmax = vp0;
                vpmid = vp1;
                vpmin = vp2;
            } else {
                vpmax = vp2;
                vpmid = vp1;
                vpmin = vp0;
            }
        } else if (vp0[1] == vp2[1]) {
            if (vp0[1] > vp1[1]) {
                vpmax = vp0;
                vpmid = vp2;
                vpmin = vp1;
            } else {
                vpmax = vp1;
                vpmid = vp0;
                vpmin = vp2;
            }
        } else if (vp1[1] == vp2[1]) {
            if (vp1[1] > vp0[1]) {
                vpmax = vp1;
                vpmid = vp2;
                vpmin = vp0;
            } else {
                vpmax = vp0;
                vpmid = vp1;
                vpmin = vp2;
            }
        } else if (vp0[1] > vp1[1]) {
            if (vp0[1] > vp2[1]) {
                //vp0 is the highest point;
                vpmax = vp0;
                if (vp1[1] > vp2[1]) {
                    //vp2 is the lowest
                    vpmin = vp2;
                    //vp1 is the middle
                    vpmid = vp1;
                } else if (vp1[1] < vp2[1]){
                    //vp1 is the lowest
                    vpmin = vp1;
                    //vp2 is the middle
                    vpmid = vp2;
                }
            } else if (vp0[1] < vp2[1]){
                //vp2 is the highest point
                vpmax = vp2;
                //vp1 is the lowest
                vpmin = vp1;
                //vp0 is the middle
                vpmid = vp0;
            }
        } else if (vp0[1] < vp1[1]) {
            if (vp1[1] > vp2[1]) {
                //vp1 is the highest
                vpmax = vp1;
                if (vp0[1] > vp2[1]) {
                    //vp2 is the lowest
                    vpmin = vp2;
                    //vp0 is the middle
                    vpmid = vp0;
                } else if (vp0[1] < vp2[1]) {
                    //vp0 is the lowest
                    vpmin = vp0;
                    //vp2 is the middle
                    vpmid = vp2;
                }
            } else if (vp1[1] < vp2[1]) {
                //vp2 is the highest point
                vpmax = vp2;
                //vp1 is the middle
                vpmid = vp1;
                //vp0 is the lowest
                vpmin = vp0;
            }
        }
    
    //sorting done;
        
        for (auto y = ymin; y <= ymax; y = y + dy) {
            if (y <= vpmax[1] && y >= vpmin[1]) {
                if ( y == vpmid[1] && y == vpmax[1]) {
                    sliceVtx.push_back(vpmid[0]);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(vpmid[2]);
                    
                    sliceVtx.push_back(vpmax[0]);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(vpmax[2]);
                }
                if ( y == vpmid[1] && y == vpmin[1]) {
                    sliceVtx.push_back(vpmid[0]);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(vpmid[2]);
                    
                    sliceVtx.push_back(vpmin[0]);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(vpmin[2]);
                }
                if (y < vpmax[1] && y > vpmin[1] && y == vpmid[1]) {
                    sliceVtx.push_back(vpmid[0]);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(vpmid[2]);
                }
                if (y > vpmid[1] && y < vpmax[1]) {
                    float k1 = (y - vpmid[1]) / (vpmax[1] - vpmid[1]);
                    float x1 = vpmid[0] + (vpmax[0] - vpmid[0]) * k1;
                    float z1 = vpmid[2] + (vpmax[2] - vpmid[2]) * k1;
//                    printf("%f, %f, %f\n",x1, y, z1);
                    sliceVtx.push_back(x1);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(z1);
                }
                if (y < vpmid[1] && y > vpmin[1]) {
                    double k1 = (y - vpmin[1]) / (vpmid[1] - vpmin[1]);
                    auto x1 = vpmin[0] + (vpmid[0] - vpmin[0]) * k1;
                    auto z1 = vpmin[2] + (vpmid[2] - vpmin[2]) * k1;
//                    printf("%f, %f, %f\n",x1, y, z1);
                    sliceVtx.push_back(x1);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(z1);
                }
                if (y < vpmax[1] && y > vpmin[1]) {
                    double k1 = (y - vpmin[1]) / (vpmax[1] - vpmin[1]);
                    auto x1 = vpmin[0] + (vpmax[0] - vpmin[0]) * k1;
                    auto z1 = vpmin[2] + (vpmax[2] - vpmin[2]) * k1;
//                    printf("%f, %f, %f\n",x1, y, z1);
                    sliceVtx.push_back(x1);
                    sliceVtx.push_back(y);
                    sliceVtx.push_back(z1);
                
            }
        }
    }
    
}
    printf("%d\n",sliceVtx.size());
	printf("%d milli seconds\n",(int)FsSubSecondTimer()-t0);
	return sliceVtx;
}


#define USE_LATTICE


std::vector <float> MakeRayIntersectionVertexArray(const YsShellExt &mesh)
{
	auto t0=FsSubSecondTimer();
	std::vector <float> rayItscVtx;
    
    //obtain boundary;
    YsVec3 min, max;
    mesh.GetBoundingBox(min,max);
    float xmin = min[0];
    float ymin = min[1];
    float zmin = min[2];
    float xmax = max[0];
    float ymax = max[1];
    float zmax = max[2];
    
    float dx = (xmax - xmin)/100;
    float dy = (ymax - ymin)/100;
    
    
    for (auto plHd = mesh.NullPolygon();true == mesh.MoveToNextPolygon(plHd);) {
        auto vtx = mesh.GetPolygonVertex(plHd);
        auto vp1 = mesh.GetVertexPosition(vtx[0]);
        auto vp2 = mesh.GetVertexPosition(vtx[1]);
        auto vp3 = mesh.GetVertexPosition(vtx[2]);

//        printf("check1\n");
        // find the boundary of triangle;
        ymax = vp1[1];
        if (vp2[1] >= ymax) {
            ymax = vp2[1];
        }
        if (vp3[1] >= ymax) {
            ymax = vp3[1];
        }
        ymin = vp1[1];
        if (vp2[1] <= ymin) {
            ymin = vp2[1];
        }
        if (vp3[1] <= ymin) {
            ymin = vp3[1];
        }
        xmax = vp1[0];
        if (vp2[0] >= xmax) {
            xmax = vp2[0];
        }
        if (vp3[0] >= xmax) {
            xmax = vp3[0];
        }
        xmin = vp1[0];
        if (vp2[0] <= xmin) {
            xmin = vp2[1];
        }
        if (vp3[0] <= xmin) {
            xmin = vp3[0];
        }
        int n = ymax / dy;
        ymax = (n+1) * dy;
        n = ymin / dy;
        ymin = (n-1) * dy;
        n = xmax / dx;
        xmax = (n+1)*dx;
        n = xmin / dx;
        xmin = (n-1)*dx;
        

        for (float y = ymin; y <= ymax; y = y + dy) {
//            printf("y: %f\n",y);

            for (float x = xmin; x <= xmax; x = x + dx) {
                // check if point is in x-y triangle
                // clock wise
                double dx1 = vp2[0] - vp1[0];
                double dx2 = vp3[0] - vp2[0];
                double dx3 = vp1[0] - vp3[0];
                double dy1 = vp2[1] - vp1[1];
                double dy2 = vp3[1] - vp2[1];
                double dy3 = vp1[1] - vp3[1];
                if ((((x - vp1[0]) * dy1 - (y - vp1[1]) * dx1) < 0) &&
                    (((x - vp2[0]) * dy2 - (y - vp2[1]) * dx2) < 0) &&
                    (((x - vp3[0]) * dy3 - (y - vp3[1]) * dx3) < 0)) {
                    // point is in the triangle
                    // calculate the plane function
                    float a = ( (vp2[1]-vp1[1])*(vp3[2]-vp1[2])-(vp2[2]-vp1[2])*(vp3[1]-vp1[1]) );
                    
                    float b = ( (vp2[2]-vp1[2])*(vp3[0]-vp1[0])-(vp2[0]-vp1[0])*(vp3[2]-vp1[2]) );
                    
                    float c = ( (vp2[0]-vp1[0])*(vp3[1]-vp1[1])-(vp2[1]-vp1[1])*(vp3[0]-vp1[0]) );
                    
                    float d = ( 0-(a*vp1[0]+b*vp1[1]+c*vp1[2]) );
                    // calculate the z
                    float z = (-d - a*x - b*y)/c;
                    // push the point x, y, z
                    // printf("x: %f, y: %f, z: %f\n",x,y,z);
                    rayItscVtx.push_back(x);
                    rayItscVtx.push_back(y);
                    rayItscVtx.push_back(z);
                }
                // conter-clock wise
                dx1 = vp3[0] - vp1[0];
                dx2 = vp1[0] - vp2[0];
                dx3 = vp2[0] - vp3[0];
                dy1 = vp3[1] - vp1[1];
                dy2 = vp1[1] - vp2[1];
                dy3 = vp2[1] - vp3[1];
                if ((((x - vp1[0]) * dy1 - (y - vp1[1]) * dx1) < 0) &&
                    (((x - vp2[0]) * dy2 - (y - vp2[1]) * dx2) < 0) &&
                    (((x - vp3[0]) * dy3 - (y - vp3[1]) * dx3) < 0)) {
                    // point is in the triangle
                    // calculate the plane function
                    float a = ( (vp2[1]-vp1[1])*(vp3[2]-vp1[2])-(vp2[2]-vp1[2])*(vp3[1]-vp1[1]) );
                    
                    float b = ( (vp2[2]-vp1[2])*(vp3[0]-vp1[0])-(vp2[0]-vp1[0])*(vp3[2]-vp1[2]) );
                    
                    float c = ( (vp2[0]-vp1[0])*(vp3[1]-vp1[1])-(vp2[1]-vp1[1])*(vp3[0]-vp1[0]) );
                    
                    float d = ( 0-(a*vp1[0]+b*vp1[1]+c*vp1[2]) );
                    // calculate the z
                    float z = (-d - a*x - b*y)/c;
                    // push the point x, y, z
                    // printf("x: %f, y: %f, z: %f\n",x,y,z);
                    rayItscVtx.push_back(x);
                    rayItscVtx.push_back(y);
                    rayItscVtx.push_back(z);
                }

            }
        }
        
    }
    

	printf("%d milli seconds\n",(int)FsSubSecondTimer()-t0);
	return rayItscVtx;
}



void Paint(YsShellExt &mesh,YsShell::PolygonHandle from,const double angleTolerance)
{
    std::unordered_set <unsigned int> visited;
    std::vector <YsShellExt::PolygonHandle> connPlHd;
    
    const double PI = 3.141592653;
    connPlHd.push_back(from);
    visited.insert(mesh.GetSearchKey(from));
    
    //get norm of the selected polygon
    auto norm = mesh.GetNormal(from);
    //Set the selected polygon to red
    mesh.SetPolygonColor(from, YsRed());
    printf("size: %d\n",connPlHd.size());
    for(int i=0; i<connPlHd.size(); ++i)
    {
        printf("check1\n");
        auto plHd=connPlHd[i];
        auto plVtHd=mesh.GetPolygonVertex(plHd);
        printf("size: %d, i: %d",plVtHd.size(),i);
        for(int e=0; e<plVtHd.size(); ++e)
        {
            auto neiPlHd=mesh.GetNeighborPolygon(plHd,e);
            if(mesh.NullPolygon()!=neiPlHd &&
               visited.end()==visited.find(mesh.GetSearchKey(neiPlHd)))
            {

                //get the norm of the neighbor polygon
                auto neinorm = mesh.GetNormal(neiPlHd);
                //calculate the dot produc
                auto dp = norm[0] * neinorm[0] + norm[1] * neinorm[1] + norm[2] * neinorm[2];
                
//                printf("norm: %d, %d, %d\n", norm[0], norm[1], norm[2]);
//                printf("neinorm: %d, %d, %d\n", neinorm[0], neinorm[1], neinorm[2]);
                
                //calculate the length
                auto l1 = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
                auto l2 = sqrt(neinorm[0] * neinorm[0] + neinorm[1] * neinorm[1] + neinorm[2] * neinorm[2]);
                //calculate the angle
                auto cos = dp / l1 / l2;
//                printf("cos : %lf\n",cos);
                auto angle = acos(cos) * 180.0 / PI;
//                printf("angle : %lf\n",angle);
                if(angle < angleTolerance) {
                    connPlHd.push_back(neiPlHd);
                    mesh.SetPolygonColor(neiPlHd, YsRed());
                    visited.insert(mesh.GetSearchKey(neiPlHd));
                }
            }
        }
    }
}
