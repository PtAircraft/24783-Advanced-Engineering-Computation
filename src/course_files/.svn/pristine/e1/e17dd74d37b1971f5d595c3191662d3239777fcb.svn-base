#include "meshlattice.h"


void MeshLatticeElem::CleanUp(void)
{
	vtHd.clear();
}

////////////////////////////////////////////////////////////
MeshLattice::MeshLattice()
{
	meshPtr=nullptr;
}

void MeshLattice::SetDomain(const PolygonalMesh &mesh,int nx,int ny,int nz)
{
	meshPtr=&mesh;

	YsVec3 min,max;
	mesh.GetBoundingBox(min,max);

	auto d=(max-min).GetLength()*0.01;
	min-=YsVec3(d,d,d);
	max+=YsVec3(d,d,d);

	Create(nx,ny,nz,min,max);

	for(auto vtHd=mesh.NullVertex(); true==mesh.MoveToNextVertex(vtHd); )
	{
		auto vtPos=mesh.GetVertexPosition(vtHd);
		auto idx=GetBlockIndex(vtPos);
		if(IsInRange(idx))
		{
			(*this)[idx].vtHd.push_back(vtHd);
		}
	}
}

std::vector <PolygonalMesh::VertexHandle> MeshLattice::FindVertex(const YsVec3 &min,const YsVec3 &max) const
{
	std::vector <PolygonalMesh::VertexHandle> allVtHd;
	auto idx0=GetBlockIndex(min);
	auto idx1=GetBlockIndex(max);

	for(int iz=idx0.z(); iz<=idx1.z(); ++iz)
	{
		for(int iy=idx0.y(); iy<=idx1.y(); ++iy)
		{
			for(int ix=idx0.x(); ix<=idx1.x(); ++ix)
			{
				YsVec3i idx(ix,iy,iz);
				if(IsInRange(idx))
				{
					for(auto vtHd : (*this)[idx].vtHd)
					{
						auto vtPos=meshPtr->GetVertexPosition(vtHd);
						if(min.x()<=vtPos.x() && vtPos.x()<=max.x() &&
						   min.y()<=vtPos.y() && vtPos.y()<=max.y() &&
						   min.z()<=vtPos.z() && vtPos.z()<=max.z())
						{
							allVtHd.push_back(vtHd);
						}
					}
				}
			}
		}
	}

	return allVtHd;
}
