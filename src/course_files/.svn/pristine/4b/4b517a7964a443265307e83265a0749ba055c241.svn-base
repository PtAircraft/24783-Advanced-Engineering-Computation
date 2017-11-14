#include "qem.h"



// My homework solutions:
// In addition to typoes,
// Error 1  VS2015 is not fully C++11 compliant.  std::unordered_map::erase cannot take const reference to key.  I need to give an iterator to erase function.
// Error 2  Vertex B is connected to multiple vertices.  So, before collapsing, I need to take out all edges connected to Vertex B from the data structure.



static void CollapseEdge(YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,YsShellExt::VertexHandle vtHd1)
{
	for(auto usingPlHd : mesh.FindPolygonFromEdgePiece(vtHd0,vtHd1))
	{
		mesh.DeletePolygon(usingPlHd);
	}

	const YsVec3 newVtPos=(mesh.GetVertexPosition(vtHd0)+mesh.GetVertexPosition(vtHd1))/2.0;
	mesh.SetVertexPosition(vtHd0,newVtPos);

	for(auto plHd : mesh.FindPolygonFromVertex(vtHd1))
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(auto &vtHd : plVtHd)
		{
			if(vtHd==vtHd1)
			{
				vtHd=vtHd0;
			}
		}
		mesh.SetPolygonVertex(plHd,plVtHd);
	}

	mesh.DeleteVertex(vtHd1);
}

double CalculateQuadricErrorMetric(
    const YsShellExt &mesh,YsShellExt::VertexHandle vtHdA,YsShellExt::VertexHandle vtHdB)
{
	const YsVec3 midPoint=(mesh.GetVertexPosition(vtHdA)+mesh.GetVertexPosition(vtHdB))/2.0;
	const YsShellExt::VertexHandle edVtHd[2]={vtHdA,vtHdB};
	double total=0.0;
	for(auto vtHd : edVtHd)
	{
		for(auto plHd : mesh.FindPolygonFromVertex(vtHd))
		{
			auto nom=mesh.GetNormal(plHd);
			auto plVtHd=mesh.GetPolygonVertex(plHd);
			auto p0=mesh.GetVertexPosition(plVtHd[0]);

			auto d=(midPoint-p0)*nom;
			total+=d*d;
		}
	}
	return total;
}

bool SimplifyWithQuadricErrorMetricOneStep(YsShellExt &mesh)
{
	double minErr=0.0;
	YsShellExt::VertexHandle minErrEdge[2]={nullptr,nullptr};
	for(YsShellEdgeEnumHandle edHd=nullptr; YSOK==mesh.MoveToNextEdge(edHd); )
	{
		auto edge=mesh.GetEdge(edHd);
		auto qem=CalculateQuadricErrorMetric(mesh,edge[0],edge[1]);
		if(nullptr==minErrEdge[0] || qem<minErr)
		{
			minErrEdge[0]=edge[0];
			minErrEdge[1]=edge[1];
			minErr=qem;
		}
	}
	if(nullptr!=minErrEdge[0])
	{
		CollapseEdge(mesh,minErrEdge[0],minErrEdge[1]);
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////

void QEMSimplifier::Start(YsShellExt &mesh)
{
	for(YsShellEdgeEnumHandle edHd=nullptr; YSOK==mesh.MoveToNextEdge(edHd); )
	{
		auto edge=mesh.GetEdge(edHd);
		auto qem=CalculateQuadricErrorMetric(mesh,edge[0],edge[1]);

		auto treeNdHd=sortedEdge.Insert(qem,edge);

		UnorderedUnsignedIntPair edgeSearchKey;
		edgeSearchKey.v[0]=mesh.GetSearchKey(edge[0]);
		edgeSearchKey.v[1]=mesh.GetSearchKey(edge[1]);
		edgeToTreeNode[edgeSearchKey]=treeNdHd;
	}
}

bool QEMSimplifier::SimplifyOneStep(YsShellExt &mesh)
{
	auto firstNdHd=sortedEdge.First();
	if(firstNdHd!=nullptr)
	{
		auto edge=sortedEdge.GetValue(firstNdHd);
		sortedEdge.Delete(firstNdHd);

		UnorderedUnsignedIntPair edgeSearchKey;
		edgeSearchKey.v[0]=mesh.GetSearchKey(edge[0]);
		edgeSearchKey.v[1]=mesh.GetSearchKey(edge[1]);
		edgeToTreeNode.erase(edgeSearchKey);

		for(auto connVtHd : mesh.GetConnectedVertex(edge[1]))
		{
			edgeSearchKey.v[0]=mesh.GetSearchKey(edge[1]);
			edgeSearchKey.v[1]=mesh.GetSearchKey(connVtHd);
			auto iter=edgeToTreeNode.find(edgeSearchKey);
			if(edgeToTreeNode.end()!=iter)
			{
				sortedEdge.Delete(edgeToTreeNode[edgeSearchKey]);
				edgeToTreeNode.erase(iter);
			}
		}

		CollapseEdge(mesh,edge[0],edge[1]); // edge[1] is deleted.

		for(auto plHd : mesh.FindPolygonFromVertex(edge[0]))
		{
			std::vector <YsVec3> plVtPos;
			for(auto vtHd : mesh.GetPolygonVertex(plHd))
			{
				plVtPos.push_back(mesh.GetVertexPosition(vtHd));
			}
			auto nom=YsGetAverageNormalVector(plVtPos.size(),plVtPos.data());
			mesh.SetPolygonNormal(plHd,nom);
		}

		for(auto connVtHd : mesh.GetConnectedVertex(edge[0]))
		{
			edgeSearchKey.v[0]=mesh.GetSearchKey(edge[0]);
			edgeSearchKey.v[1]=mesh.GetSearchKey(connVtHd);
			auto iter=edgeToTreeNode.find(edgeSearchKey);
			if(edgeToTreeNode.end()!=iter)
			{
				sortedEdge.Delete(edgeToTreeNode[edgeSearchKey]);
				edgeToTreeNode.erase(iter);
			}

			YsShellExt::Edge newEdge;
			newEdge[0]=edge[0];
			newEdge[1]=connVtHd;

			auto qem=CalculateQuadricErrorMetric(mesh,edge[0],connVtHd);
			auto treeNdHd=sortedEdge.Insert(qem,newEdge);
			edgeToTreeNode[edgeSearchKey]=treeNdHd;
		}
		for(auto plHd : mesh.FindPolygonFromVertex(edge[0]))
		{
			auto plVtHd=mesh.GetPolygonVertex(plHd);
			for(int edIdx=0; edIdx<plVtHd.size(); ++edIdx)
			{
				YsShellExt::VertexHandle edVtHd[2]=
				{
					plVtHd[edIdx],
					plVtHd.GetCyclic(edIdx+1)
				};

				if(edge[0]!=edVtHd[0] && edge[0]!=edVtHd[1])
				{
					edgeSearchKey.v[0]=mesh.GetSearchKey(edVtHd[0]);
					edgeSearchKey.v[1]=mesh.GetSearchKey(edVtHd[1]);
					auto iter=edgeToTreeNode.find(edgeSearchKey);
					if(edgeToTreeNode.end()!=iter)
					{
						sortedEdge.Delete(edgeToTreeNode[edgeSearchKey]);
						edgeToTreeNode.erase(iter);
					}

					YsShellExt::Edge newEdge;
					newEdge[0]=edVtHd[0];
					newEdge[1]=edVtHd[1];

					auto qem=CalculateQuadricErrorMetric(mesh,newEdge[0],newEdge[1]);
					auto treeNdHd=sortedEdge.Insert(qem,newEdge);
					edgeToTreeNode[edgeSearchKey]=treeNdHd;
				}
			}
		}
		return true;
	}
	return false;
}
