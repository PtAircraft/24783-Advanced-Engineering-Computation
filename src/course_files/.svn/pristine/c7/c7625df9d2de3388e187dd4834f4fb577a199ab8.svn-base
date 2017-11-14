#include <stdio.h>
#include <ysshellext.h>


int main(int argc,char *argv[])
{
	if(2==argc)
	{
		YsShellExt shl;
		if(YSOK==shl.LoadStl(argv[1]))
		{
			shl.EnableSearch();

			bool openMesh=false,nonManifold=false;

			// for(auto plHd=shl.NullPolygon(); true==shl.MoveToNextPolygon(plHd); )
			for(auto plHd : shl.AllPolygon())
			{
				// YsArray <YsShell::VertexHandle>
				auto plVtHd=shl.GetPolygonVertex(plHd);
				for(int i=0; i<plVtHd.size(); ++i)
				{
					YsShellExt::VertexHandle edVtHd[2]=
					{
						plVtHd[i],
						plVtHd.GetCyclic(i+1) // plVtHd[(i+1)%plVtHd.size()]
					};
					auto edPlHd=shl.FindPolygonFromEdgePiece(edVtHd[0],edVtHd[1]);
					if(1==edPlHd.size())
					{
						openMesh=true;
					}
					else if(2<edPlHd.size())
					{
						nonManifold=true;
						break;
					}
				}
				if(true==nonManifold)
				{
					break;
				}
			}

			if(true==nonManifold)
			{
				printf("It is a non-manifold mesh.\n");
			}
			else if(true==openMesh)
			{
				printf("It is an open mesh.\n");
			}
			else
			{
				printf("It is a manifold mesh.\n");
			}
		}
	}

	return 0;
}

