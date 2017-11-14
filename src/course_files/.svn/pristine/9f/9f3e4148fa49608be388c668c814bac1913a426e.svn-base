#include "naca4digit.h"
#include <polygonalmesh.h>

std::vector <YsVec3> MakeNACA4DigitAirfoil(int naca,const double dz)
{
	std::vector <YsVec3> vtx;

	std::vector <float> up,down;

	float c=1.0;
	float t=(float)(naca%100)/100.0f;
	float m=(float)((naca/1000)%10)/100.0f;
	float p=(float)((naca/100)%10)/10.0f;

	float z=0.0;
	for(;;)
	{
		if(1.0f<z)
		{
			z=1.0f;
		}

		float yt=5.0f*t*c*(0.2969*sqrt(z/c)-0.1260*(z/c)-0.3516*(z*z)/(c*c)+0.2843*(z*z*z)/(c*c*c)-0.1015*(z*z*z*z)/(c*c*c*c));
		float yc=0.0f;
		if(0<=z && z<p*c)
		{
			yc=((m*z)/(p*p))*(2.0f*p-z/c);
		}
		else
		{
			yc=m*((c-z)/((1-p)*(1-p))*(1+z/c-2.0f*p));
		}

		up.push_back(z);
		up.push_back(yc+yt);
		down.push_back(z);
		down.push_back(yc-yt);

		if(1.0f<=z)
		{
			break;
		}
		z+=dz;
	}

	for(int i=0; i<=up.size()-2; i+=2)
	{
		vtx.push_back(YsVec3(0,up[i+1],up[i]));
	}
	for(int i=down.size()-2; 0<=i; i-=2)
	{
		vtx.push_back(YsVec3(0,down[i+1],down[i]));
	}

	return vtx;
}

void MakeNACA4DigitWing(class PolygonalMesh &mesh,int naca,const double span,const double sweepBack,const double dihedral,const double tapar,const double dz)
{
	auto airfoil=MakeNACA4DigitAirfoil(naca,dz);
	std::vector <PolygonalMesh::VertexHandle> center,left,right;

	for(auto v : airfoil)
	{
		auto y=v.y();
		auto z=v.z();

		center.push_back(mesh.AddVertex(YsVec3(0,y,z)));
		left.push_back(mesh.AddVertex(YsVec3(-span,y*tapar+dihedral,z*tapar+sweepBack)));
		right.push_back(mesh.AddVertex(YsVec3(span,y*tapar+dihedral,z*tapar+sweepBack)));
	}

	for(int i=0; i<airfoil.size()-1; ++i)
	{
		PolygonalMesh::VertexHandle quad[2][4]=
		{
			{
				center[i],center[i+1],right[i+1],right[i]
			},
			{
				center[i+1],center[i],left[i],left[i+1]
			}
		};
		for(int j=0; j<2; ++j)
		{
			PolygonalMesh::VertexHandle triVtHd[2][3]=
			{
				{quad[j][0],quad[j][1],quad[j][2]},
				{quad[j][2],quad[j][3],quad[j][0]},
			};
			for(int k=0; k<2; ++k)
			{
				auto plHd=mesh.AddPolygon(3,triVtHd[k]);
				YsVec3 triVtPos[3]=
				{
					mesh.GetVertexPosition(triVtHd[k][0]),
					mesh.GetVertexPosition(triVtHd[k][1]),
					mesh.GetVertexPosition(triVtHd[k][2]),
				};
				YsVec3 v1=YsUnitVector(triVtPos[1]-triVtPos[0]);
				YsVec3 v2=YsUnitVector(triVtPos[2]-triVtPos[0]);
				YsVec3 nom=YsUnitVector(v1^v2);
				mesh.SetPolygonNormal(plHd,nom);
				mesh.SetPolygonColor(plHd,YsBlue());
			}
		}
	}
}

