#ifndef MESHLATTICE_IS_INCLUDED
#define MESHLATTICE_IS_INCLUDED

#include <vector>
#include <polygonalmesh.h>
#include "lattice.h"

class MeshLatticeElem
{
public:
    std::vector <PolygonalMesh::VertexHandle> vtHd;
    void CleanUp(void);
};

class MeshLattice : public Lattice3d <MeshLatticeElem>
{
private:
	const PolygonalMesh *meshPtr;
public:
	MeshLattice();
    void SetDomain(const PolygonalMesh &mesh,int nx,int ny,int nz);
    std::vector <PolygonalMesh::VertexHandle> FindVertex(const YsVec3 &min,const YsVec3 &max) const;
};

#endif
