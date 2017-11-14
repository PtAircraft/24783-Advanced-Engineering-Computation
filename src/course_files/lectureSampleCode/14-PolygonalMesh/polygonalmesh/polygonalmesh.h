#ifndef POLYGONALMESH_IS_INCLUDED
#define POLYGONALMESH_IS_INCLUDED

#include <list>
#include <unordered_map>

#include <ysclass.h>

class PolygonalMesh
{
protected:
    class Vertex
    {
    public:
        YsVec3 pos;
        unsigned int searchKey;
    };
public:
    class VertexHandle
    {
    friend class PolygonalMesh;
    private:
    	unsigned int searchKey;
        std::list <Vertex>::iterator vtxPtr;
	public:
        VertexHandle(){};  // C++11 VertexHandle()=default;
        bool operator==(const VertexHandle &vtHd) const
        {
			return vtHd.vtxPtr==vtxPtr;
		}
        bool operator!=(const VertexHandle &vtHd) const
        {
			return vtHd.vtxPtr!=vtxPtr;
		}
    };
protected:
    class Polygon
    {
    public:
        std::vector <VertexHandle> vtHd;
        YsVec3 nom;
        YsColor col; // Defined in ysproperty.h
        unsigned int searchKey;
    };
public:
    class PolygonHandle
    {
    friend class PolygonalMesh;
    private:
        std::list <Polygon>::iterator plgPtr;
    public:
        PolygonHandle(){};  // C++11 PolygonHandle()=default;
        inline bool operator==(const PolygonHandle &plHd) const
        {
			return plHd.plgPtr==plgPtr;
		}
        inline bool operator!=(const PolygonHandle &plHd) const
        {
			return plHd.plgPtr!=plgPtr;
		}
    };


private:
	unsigned int searchKeySeed;
    mutable std::list <Vertex> vtxList;
    mutable std::list <Polygon> plgList;

	std::unordered_map <unsigned int,VertexHandle> vtxSearch;
	std::unordered_map <unsigned int,std::vector <PolygonHandle> > vtKeyToPlg;


public:
	PolygonalMesh();


    VertexHandle AddVertex(const YsVec3 &pos);
	bool DeleteVertex(VertexHandle vtHd);

    inline VertexHandle NullVertex(void) const
	{
		VertexHandle vtHd;
		vtHd.vtxPtr=vtxList.end();
		return vtHd;
	}
    YsVec3 GetVertexPosition(VertexHandle vtHd) const;
    void SetVertexPosition(VertexHandle vtHd,const YsVec3 &newPos);
	long long int GetNumVertex(void) const;
    bool MoveToNextVertex(VertexHandle &vtHd) const;
    unsigned int GetSearchKey(VertexHandle vtHd) const;
    std::vector <PolygonHandle> FindPolygonFromVertex(VertexHandle vtHd) const;

	std::vector <VertexHandle> GetConnectedVertex(VertexHandle fromVtHd) const;
	std::vector <PolygonalMesh::PolygonHandle> PolygonalMesh::FindPolygonFromEdgePiece(VertexHandle edVtHd0,VertexHandle edVtHd1) const;
	PolygonHandle GetNeighborPolygon(PolygonHandle plHd,int n) const;


    PolygonHandle AddPolygon(int nPlVt,const VertexHandle plVtHd[]);
    PolygonHandle AddPolygon(const std::vector <VertexHandle> &plVtHd);
    inline PolygonHandle NullPolygon(void) const
    {
		PolygonHandle plHd;
		plHd.plgPtr=plgList.end();
		return plHd;
	}
	unsigned int GetSearchKey(PolygonHandle plHd) const;
    const std::vector <VertexHandle> GetPolygonVertex(PolygonHandle plHd) const;
    long long int GetNumPolygon(void) const;
    bool MoveToNextPolygon(PolygonHandle &plHd) const;

    bool SetPolygonColor(PolygonHandle plHd,YsColor col);
    YsColor GetColor(PolygonHandle plHd) const;
    bool SetPolygonNormal(PolygonHandle plHd,const YsVec3 &nom);
    YsVec3 GetNormal(PolygonHandle plHd) const;
	YsVec3 GetCenter(PolygonHandle plHd) const;

public:
    bool SetPolygonVertex(PolygonHandle plHd,const std::vector <VertexHandle> &newPlVtHd);
protected:
    void UnregisterPolygon(PolygonHandle plHd);
    void UnregisterPolygonFromVertex(PolygonHandle plHd,VertexHandle vtHd);
    void RegisterPolygon(PolygonHandle plHd);


public:
	bool SaveBinStl(const char fn[]) const;

public:
	bool LoadBinStl(const char fn[]);

private:
	bool IsASCIIStl(const char fn[]);
	bool IsLittleEndian(void);
	unsigned int BinaryToInt(const unsigned char dat[4]);
	float BinaryToFloat(const unsigned char dat[4]);

public:
	void GetBoundingBox(YsVec3 &min,YsVec3 &max) const;

public:
	void MergeVertex(const double tol);
};

#endif