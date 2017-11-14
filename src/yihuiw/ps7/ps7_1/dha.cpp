#include "dha.h"

#include <unordered_set>

// Input parameters are a mesh and dihedral-angle threshold.
// The return value is a map from a polygon search key to a segment identifier.
std::unordered_map <YSHASHKEY,int> MakeDihedralAngleBasedSegmentation(const YsShellExt &mesh,const double dhaThr)
{
	std::unordered_map <YSHASHKEY,int> faceGrp;
    int group = 1;
    const double PI = 3.141592653;
    std::unordered_set <unsigned int> visited;

    for (auto ploHd = mesh.NullPolygon();true == mesh.MoveToNextPolygon(ploHd);) {
        
        std::vector <YsShellExt::PolygonHandle> connPlHd;
        
        connPlHd.push_back(ploHd);
        
        auto it = faceGrp.find(mesh.GetSearchKey(ploHd));
        if (it != faceGrp.end()) {
            continue;
        }
        
        for(int i=0; i<connPlHd.size(); ++i)
        {
            auto plHd=connPlHd[i];
            
            faceGrp[mesh.GetSearchKey(plHd)] = group;
            
            //get norm center polygon
            auto norm = mesh.GetNormal(plHd);
            
            // get connected polygon
            auto plVtHd=mesh.GetPolygonVertex(plHd);
            
            for(int e=0; e<plVtHd.size(); ++e)
            {
                // get neighbor polygon
                auto neiPlHd=mesh.GetNeighborPolygon(plHd,e);
                
                //get the norm of the neighbor polygon
                auto neinorm = mesh.GetNormal(neiPlHd);

                if(mesh.NullPolygon()!=neiPlHd &&
                   visited.end()==visited.find(mesh.GetSearchKey(neiPlHd)) &&  norm * neinorm > cos(dhaThr))
                {
                    if (norm * neinorm > cos(dhaThr)) {
                        connPlHd.push_back(neiPlHd);
                        visited.insert(mesh.GetSearchKey(neiPlHd));
                    }

                    
                }
            }
        }
        group = group + 1;
    }
//    printf("group: %d\n",group);

	return faceGrp;
}

// Input parameters are a mesh and the segmentation (face grouping) obtained from MakeDihedralAngleBasedSegmentaion.
// Output is a vertex array that can be drawn as GL_LINES.
std::vector <float> MakeGroupBoundaryVertexArray(const YsShellExt &mesh,const std::unordered_map <YSHASHKEY,int> &faceGroupInfo)
{
	std::vector <float> vtxArray;
    std::unordered_map <YSHASHKEY,int> faceGrp;
    int group = 1;
    const double PI = 3.141592653;
    std::unordered_set <unsigned int> visited;
    
    for (auto ploHd = mesh.NullPolygon();true == mesh.MoveToNextPolygon(ploHd);) {
        
        std::vector <YsShellExt::PolygonHandle> connPlHd;
        
        connPlHd.push_back(ploHd);
        
        auto it = faceGrp.find(mesh.GetSearchKey(ploHd));
        if (it != faceGrp.end()) {
            continue;
        }
        
        for(int i=0; i<connPlHd.size(); ++i)
        {
            auto plHd=connPlHd[i];
            
            faceGrp[mesh.GetSearchKey(plHd)] = group;
            
            //get norm center polygon
            auto norm = mesh.GetNormal(plHd);
            
            // get the key
            auto keyc = mesh.GetSearchKey(plHd);
            
            // get connected polygon
            auto plVtHd=mesh.GetPolygonVertex(plHd);
            
            for(int e=0; e<plVtHd.size(); ++e)
            {
                // get neighbor polygon
                auto neiPlHd=mesh.GetNeighborPolygon(plHd,e);
                
                // get the norm of the neighbor polygon
                auto neinorm = mesh.GetNormal(neiPlHd);
                
                // get key of neighbor polygon
                auto keyn = mesh.GetSearchKey(neiPlHd);
                
                if(mesh.NullPolygon()!=neiPlHd &&
                   visited.end()==visited.find(mesh.GetSearchKey(neiPlHd)))
                {
                    auto idc = faceGroupInfo.find(keyc)->second;
                    auto idn = faceGroupInfo.find(keyn)->second;
                    if (idc != idn) {
                        YsVec3 v1 = mesh.GetVertexPosition(plVtHd.at(e));
                        YsVec3 v2 = mesh.GetVertexPosition(plVtHd.at((e + 1) % 3));
                        vtxArray.push_back(v1[0]);
                        vtxArray.push_back(v1[1]);
                        vtxArray.push_back(v1[2]);
                        vtxArray.push_back(v2[0]);
                        vtxArray.push_back(v2[1]);
                        vtxArray.push_back(v2[2]);
                    }

                }
            }
        }
        group = group + 1;
    }
    
	return vtxArray;
}

// For bonus questions:
// Input parameters are a mesh and the segmentation (face grouping) obtained from MakeDihedralAngleBasedSegmentaion.
// Paint polygons so that no two neighboring face groups have a same color.
void MakeFaceGroupColorMap(YsShellExt &mesh,const std::unordered_map <YSHASHKEY,int> &faceGroupInfo)
{
    for( auto fp : faceGroupInfo ) {
//        printf("check2\n");
//        printf("%d\n",fp.second);
        if (fp.second % 5 == 1) {
            auto key = fp.first;
            auto plHd = mesh.FindPolygon(key);
            mesh.SetPolygonColor(plHd, YsRed());
        }
        if (fp.second % 5 == 2) {
            auto key = fp.first;
            auto plHd = mesh.FindPolygon(key);
            mesh.SetPolygonColor(plHd, YsBlue());
        }
        if (fp.second % 5 == 3) {
            auto key = fp.first;
            auto plHd = mesh.FindPolygon(key);
            mesh.SetPolygonColor(plHd, YsWhite());
        }
        if (fp.second % 5 == 4) {
            auto key = fp.first;
            auto plHd = mesh.FindPolygon(key);
            mesh.SetPolygonColor(plHd, YsYellow());
        }
        if (fp.second % 5 == 0) {
            auto key = fp.first;
            auto plHd = mesh.FindPolygon(key);
            mesh.SetPolygonColor(plHd, YsGreen());
        }
    }
}

