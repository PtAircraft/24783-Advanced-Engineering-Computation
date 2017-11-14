#ifndef NACA4DIGIT_IS_INCLUDED
#define NACA4DIGIT_IS_INCLUDED

#include <vector>
#include <cstddef>
#include <ysclass.h>
std::vector <YsVec3> MakeNACA4DigitAirfoil(int naca,const double dz);
void MakeNACA4DigitWing(class PolygonalMesh &mesh,int naca,const double s,const double b,const double d,const double p,const double dz);

#endif
