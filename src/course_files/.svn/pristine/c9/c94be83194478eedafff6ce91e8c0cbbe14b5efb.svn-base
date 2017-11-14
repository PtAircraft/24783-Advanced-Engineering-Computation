#include <fssimplewindow.h> // For FsSubSecondTimer
#include <meshlattice.h>

#include "ps6lib.h"

std::vector <float> MakeSliceVertexArray(const YsShellExt &mesh)
{
	std::vector <float> sliceVtx;

	YsVec3 min,max;
	mesh.GetBoundingBox(min,max);

	auto t0=FsSubSecondTimer();

	double sliceInterval=(max.y()-min.y())/100.0;

	sliceVtx.clear();
	for(auto plHd : mesh.AllPolygon())
	{
		YsArray <YsVec3,4> plVtPos;
		mesh.GetPolygon(plVtPos,plHd);

		if(3==plVtPos.GetN())
		{
			double plMinY=plVtPos[0].y();
			double plMaxY=plVtPos[0].y();

			for(auto p : plVtPos)
			{
				YsMakeSmaller(plMinY,p.y());
				YsMakeGreater(plMaxY,p.y());
			}

			int sliceMin=(int)((plMinY-min.y())/sliceInterval)+1;
			int sliceMax=(int)((plMaxY-min.y())/sliceInterval);
			for(int slice=sliceMin; slice<=sliceMax; ++slice)
			{
				int n=0;
				YsVec3 itsc[2];
				const double sliceY=min.y()+(double)slice*sliceInterval;
				for(int edIdx=0; edIdx<3; ++edIdx)
				{
					YsVec3 edVtPos[2]={plVtPos[edIdx],plVtPos.GetCyclic(edIdx+1)};
					if(edVtPos[0].y()>edVtPos[1].y())
					{
						YsSwapSomething(edVtPos[0],edVtPos[1]);
					}
					if(edVtPos[0].y()<=sliceY && sliceY<=edVtPos[1].y() && edVtPos[0].y()<edVtPos[1].y())
					{
						auto dy=sliceY-edVtPos[0].y();
						auto v=edVtPos[1]-edVtPos[0];
						auto i=edVtPos[0]+v*dy/v.y();
						if(n<2)
						{
							itsc[n++]=i;
						}
					}
				}
				if(2<=n)
				{
					sliceVtx.push_back(itsc[0].x());
					sliceVtx.push_back(itsc[0].y());
					sliceVtx.push_back(itsc[0].z());
					sliceVtx.push_back(itsc[1].x());
					sliceVtx.push_back(itsc[1].y());
					sliceVtx.push_back(itsc[1].z());
				}
			}
		}
	}

	printf("%d milli seconds\n",(int)FsSubSecondTimer()-t0);
	return sliceVtx;
}


#define USE_LATTICE


std::vector <float> MakeRayIntersectionVertexArray(const YsShellExt &mesh)
{
	std::vector <float> rayItscVtx;
	rayItscVtx.clear();

	auto t0=FsSubSecondTimer();

	YsVec3 min,max;
	mesh.GetBoundingBox(min,max);

	// Slowest method
#ifdef SLOWEST
	for(int i=0; i<100; ++i)
	{
		for(int j=0; j<100; ++j)
		{
			YsVec3 d=max-min;
			YsVec3 o=YsVec3(
				min.x()+d.x()*double(i)/100.0,
				min.y()+d.y()*double(j)/100.0,
				min.z()
			);

			for(auto plHd : mesh.AllPolygon())
			{
				auto plVtHd=mesh.GetPolygonVertex(plHd);
				const YsVec3 tri[3]=
				{
					mesh.GetVertexPosition(plVtHd[0]),
					mesh.GetVertexPosition(plVtHd[1]),
					mesh.GetVertexPosition(plVtHd[2]),
				};
				YsPlane pln;
				pln.MakePlaneFromTriangle(tri[0],tri[1],tri[2]);

				YsVec3 itsc;
				if(YSOK==pln.GetIntersection(itsc,o,YsZVec()))
				{
					auto side=YsCheckInsideTriangle3(itsc,tri);
					if(YSINSIDE==side || YSBOUNDARY==side)
					{
						rayItscVtx.push_back(itsc.x());
						rayItscVtx.push_back(itsc.y());
						rayItscVtx.push_back(itsc.z());
					}
				}
			}
		}
	}
#else if(defined(USE_LATTICE))
	auto d=max-min;
	auto cen=(max+min)/2.0;

	printf("Making lattice...\n");

	MeshLattice ltc;
	ltc.SetDomain(mesh,64,64,1);

	printf("Done making lattice...\n");

	for(int i=0; i<100; ++i)
	{
		for(int j=0; j<100; ++j)
		{
			YsVec3 d=max-min;
			YsVec3 o=YsVec3(
				min.x()+d.x()*double(i)/99.0,
				min.y()+d.y()*double(j)/99.0,
				cen.z()
			);

			auto idx=ltc.GetBlockIndex(o);
			if(true==ltc.IsInRange(idx))
			{
				for(auto plHd : ltc[idx].plHd)
				{
					auto plVtHd=mesh.GetPolygonVertex(plHd);
					const YsVec3 tri[3]=
					{
						mesh.GetVertexPosition(plVtHd[0]),
						mesh.GetVertexPosition(plVtHd[1]),
						mesh.GetVertexPosition(plVtHd[2]),
					};
					YsPlane pln;
					pln.MakePlaneFromTriangle(tri[0],tri[1],tri[2]);

					YsVec3 itsc;
					if(YSOK==pln.GetIntersection(itsc,o,YsZVec()))
					{
						auto side=YsCheckInsideTriangle3(itsc,tri);
						if(YSINSIDE==side || YSBOUNDARY==side)
						{
							rayItscVtx.push_back(itsc.x());
							rayItscVtx.push_back(itsc.y());
							rayItscVtx.push_back(itsc.z());
						}
					}
				}
			}
		}
	}
#endif

	printf("%d milli seconds\n",(int)FsSubSecondTimer()-t0);

	return rayItscVtx;
}

void Paint(YsShellExt &mesh,YsShell::PolygonHandle from,const double angleTolerance)
{
	std::vector <YsShell::PolygonHandle> todo;
	YsShellPolygonStore visited(mesh.Conv());
	auto nom0=mesh.GetNormal(from);

	mesh.SetPolygonColor(from,YsRed());

	todo.push_back(from);
	visited.Add(from);
	while(0<todo.size())
	{
		auto plHd=todo.back();
		todo.pop_back();

		auto nEdge=mesh.GetPolygonNumVertex(plHd);
		for(int edIdx=0; edIdx<nEdge; ++edIdx)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,edIdx);
			if(nullptr!=neiPlHd &&
			   YSTRUE!=visited.IsIncluded(neiPlHd) &&
			   cos(angleTolerance)<mesh.GetNormal(neiPlHd)*nom0)
			{
				mesh.SetPolygonColor(neiPlHd,YsRed());
				visited.Add(neiPlHd);
				todo.push_back(neiPlHd);
			}
		}
	}
}
