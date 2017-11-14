#include "polygonalmesh.h"
#include <stdio.h>

int main(void)
{
    PolygonalMesh s;
    std::vector <PolygonalMesh::VertexHandle> vtHdArray;
    vtHdArray.push_back(s.AddVertex(YsVec3(-3,-3,-3)));
    vtHdArray.push_back(s.AddVertex(YsVec3( 3,-3,-3)));
    vtHdArray.push_back(s.AddVertex(YsVec3( 3,-3, 3)));
    vtHdArray.push_back(s.AddVertex(YsVec3(-3,-3, 3)));
    vtHdArray.push_back(s.AddVertex(YsVec3(-3, 3,-3)));
    vtHdArray.push_back(s.AddVertex(YsVec3( 3, 3,-3)));
    vtHdArray.push_back(s.AddVertex(YsVec3( 3, 3, 3)));
    vtHdArray.push_back(s.AddVertex(YsVec3(-3, 3, 3)));

	for(auto vtHd=s.NullVertex(); true==s.MoveToNextVertex(vtHd); )
	{
		auto pos=s.GetVertexPosition(vtHd);
		printf("V (%lf %lf %lf)\n",pos.x(),pos.y(),pos.z());
	}


    int plgVtx[6][4]=
    {
        {0,1,2,3},{7,6,5,4},{1,0,5,4},{2,1,5,6},{3,2,6,7},{0,3,7,4}
    };
    for(auto pv : plgVtx)
    {
        std::vector<PolygonalMesh::VertexHandle> plVtHd;
        plVtHd.push_back(vtHdArray[pv[0]]);
        plVtHd.push_back(vtHdArray[pv[1]]);
        plVtHd.push_back(vtHdArray[pv[2]]);
        plVtHd.push_back(vtHdArray[pv[3]]);
        s.AddPolygon(plVtHd);
    }

	for(auto plHd=s.NullPolygon(); true==s.MoveToNextPolygon(plHd); )
	{
		auto plVtHd=s.GetPolygonVertex(plHd);
		printf("P %d\n",(int)plVtHd.size());
		for(auto vtHd : plVtHd)
		{
			auto pos=s.GetVertexPosition(vtHd);
			printf("(%lf %lf %lf)\n",pos.x(),pos.y(),pos.z());
		}
	}

	for(auto vtHd=s.NullVertex(); true==s.MoveToNextVertex(vtHd); )
	{
		auto found=s.FindPolygonFromVertex(vtHd);
		printf("Vertex %d is used from %d polygons.\n",(int)s.GetSearchKey(vtHd),(int)found.size());
		for(auto plHd : found)
		{
			auto plVtHd=s.GetPolygonVertex(plHd);
//			bool isIncluded=false;
//			for(auto tstVtHd : plVtHd)
//			{
//				if(tstVtHd==vtHd)
//				{
//					isIncluded=true;
//					break;
//				}
//			}
//			if(true!=isIncluded)

			if(plVtHd.end()==std::find(plVtHd.begin(),plVtHd.end(),vtHd))
			{
				printf("Vtx->Plg table broken.\n");
			}
		}
	}

	return 0;
}
