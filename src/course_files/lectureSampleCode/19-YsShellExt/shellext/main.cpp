#include <vector>
#include <unordered_set>

#include <ysclass.h>

#include <fslazywindow.h>

#include <ysshellext.h>
#include <qem.h>

#include "shelllattice.h"

#include "glutil.h"


////////////////////////////////////////////////////////////

std::vector <YsShellExt::PolygonHandle> GetConnectedPolygon(
    const YsShellExt &mesh,YsShellExt::PolygonHandle plHd0)
{
	std::unordered_set <unsigned int> visited;
	std::vector <YsShellExt::PolygonHandle> connPlHd;

	connPlHd.push_back(plHd0);
	visited.insert(mesh.GetSearchKey(plHd0));
	for(int i=0; i<connPlHd.size(); ++i)
	{
		auto plHd=connPlHd[i];
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(int e=0; e<plVtHd.size(); ++e)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,e);
			if(mesh.NullPolygon()!=neiPlHd &&
			   visited.end()==visited.find(mesh.GetSearchKey(neiPlHd)))
			{
				connPlHd.push_back(neiPlHd);
				visited.insert(mesh.GetSearchKey(neiPlHd));
			}
		}
	}

	return connPlHd;
}

std::vector <YsShellExt::VertexHandle> GetNNeighbor(
    const YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,int dist)
{
	std::unordered_set <unsigned int> visited;
	std::vector <YsShellExt::VertexHandle> connVtHd;
	std::vector <int> connVtHdDist;

	connVtHd.push_back(vtHd0);
	connVtHdDist.push_back(0);
	visited.insert(mesh.GetSearchKey(vtHd0));

	for(int i=0; i<connVtHd.size(); ++i)
	{
		if(connVtHdDist[i]<dist)
		{
			auto vtHd=connVtHd[i];
			auto curDist=connVtHdDist[i];
			for(auto neiVtHd : mesh.GetConnectedVertex(vtHd))
			{
				if(visited.end()==visited.find(mesh.GetSearchKey(neiVtHd)))
				{
					connVtHd.push_back(neiVtHd);
					connVtHdDist.push_back(curDist+1);
					visited.insert(mesh.GetSearchKey(neiVtHd));
				}
			}
		}
	}

	return connVtHd;
}

std::vector <YsShellExt::VertexHandle> GreedyPathSearch(
   const YsShellExt &shl,YsShellExt::VertexHandle startVtHd,YsShellExt::VertexHandle goalVtHd)
{
	std::vector <YsShellExt::VertexHandle> path;

	auto curVtHd=startVtHd;
	auto curDist=(shl.GetVertexPosition(curVtHd)-shl.GetVertexPosition(goalVtHd)).GetLength();
	path.push_back(startVtHd);
	while(curVtHd!=goalVtHd)
	{
		auto nextVtHd=curVtHd;
		auto nextDist=curDist;

		for(auto vtHd : shl.GetConnectedVertex(curVtHd))
		{
			auto dist=(shl.GetVertexPosition(vtHd)-shl.GetVertexPosition(goalVtHd)).GetLength();
			if(dist<nextDist)
			{
				nextVtHd=vtHd;
				nextDist=dist;
			}
		}

		if(nextVtHd!=curVtHd)
		{
			path.push_back(nextVtHd);
			curVtHd=nextVtHd;
			curDist=nextDist;
		}
		else
		{
			break;
		}
	}

	return path;
}

class ColorPalette
{
public:
	std::vector <YsColor> palette;
	ColorPalette();
	YsColor PickColor(const std::vector <YsColor> &neiCol);
};
ColorPalette::ColorPalette()
{
	palette.push_back(YsBlue());
	palette.push_back(YsRed());
	palette.push_back(YsMagenta());
	palette.push_back(YsGreen());
	palette.push_back(YsYellow());
	palette.push_back(YsDarkBlue());
	palette.push_back(YsDarkRed());
	palette.push_back(YsDarkMagenta());
	palette.push_back(YsDarkGreen());
	palette.push_back(YsDarkYellow());
	palette.push_back(YsBlack());
	palette.push_back(YsWhite());
}
YsColor ColorPalette::PickColor(const std::vector <YsColor> &neiCol)
{
	for(auto c : palette)
	{
		bool included=false;
		for(auto n : neiCol)
		{
			if(n==c)
			{
				included=true;
				break;
			}
		}
		if(true!=included)
		{
			return c;
		}
	}

	for(int r=0; r<256; ++r)
	{
		for(int g=0; g<256; ++g)
		{
			for(int b=0; b<256; ++b)
			{
				YsColor newCol;
				newCol.SetIntRGB(r,g,b);
				bool included=false;
				for(auto c : palette)
				{
					if(c==newCol)
					{
						included=true;
						break;
					}
				}
				if(true!=included)
				{
					palette.push_back(newCol);
					return newCol;
				}
			}
		}
	}

	return YsWhite();
}

void ColorMap(YsShellExt &mesh)
{
	for(auto plHd : mesh.AllPolygon())
	{
		mesh.SetPolygonColor(plHd,YsWhite());
	}

	ColorPalette pal;
	for(auto plHd : mesh.AllPolygon())
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		std::vector <YsColor> neiPlCol;
		for(int i=0; i<plVtHd.size(); ++i)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,i);
			if(nullptr!=neiPlHd)
			{
				neiPlCol.push_back(mesh.GetColor(neiPlHd));
			}
		}

		mesh.SetPolygonColor(plHd,pal.PickColor(neiPlCol));
	}
}


////////////////////////////////////////////////////////////


// VtHd1 will be deleted.
void CollapseEdge(YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,YsShellExt::VertexHandle vtHd1)
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



////////////////////////////////////////////////////////////

class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	enum
	{
		NORMAL_MODE,
		DUAL_MODE
	};
	int mode;

	bool needRedraw;

	QEMSimplifier simplifier;

	YsMatrix4x4 Rc;
	double d;
	YsVec3 t;

	YsShellExt mesh;
	std::vector <float> vtx,nom,col;
	std::vector <float> highDhaEdgeVtx;
	YsVec3 bbx[2];

	std::vector <float> highlightVtx;

	std::vector <float> dualVtx;

	std::vector <float> pathVtx;

	YsVec3 lineOfLastPick[2];
	YsShellExt::VertexHandle lastPickedVtHd[2];
	YsShellExt::PolygonHandle lastPickedPlHd;

	static void AddColor(std::vector <float> &col,float r,float g,float b,float a);
	static void AddVertex(std::vector <float> &vtx,float x,float y,float z);
	static void AddNormal(std::vector <float> &nom,float x,float y,float z);

	void RemakeVertexArray(void);
	void RemakeDualVertexArray(void);
	YsMatrix4x4 GetProjection(void) const;
	YsMatrix4x4 GetModelView(void) const;
	YsShellExt::PolygonHandle PickedPlHd(int mx,int my) const;
	YsShellExt::VertexHandle PickedVtHd(int mx,int my,int pixRange) const;

public:
	FsLazyWindowApplication();
	virtual void BeforeEverything(int argc,char *argv[]);
	virtual void GetOpenWindowOption(FsOpenWindowOption &OPT) const;
	virtual void Initialize(int argc,char *argv[]);
	virtual void Interval(void);
	virtual void BeforeTerminate(void);
	virtual void Draw(void);
	virtual bool UserWantToCloseProgram(void);
	virtual bool MustTerminate(void) const;
	virtual long long int GetMinimumSleepPerInterval(void) const;
	virtual bool NeedRedraw(void) const;
};

/* static */ void FsLazyWindowApplication::AddColor(std::vector <float> &col,float r,float g,float b,float a)
{
	col.push_back(r);
	col.push_back(g);
	col.push_back(b);
	col.push_back(a);
}
/* static */ void FsLazyWindowApplication::AddVertex(std::vector <float> &vtx,float x,float y,float z)
{
	vtx.push_back(x);
	vtx.push_back(y);
	vtx.push_back(z);
}
/* static */ void FsLazyWindowApplication::AddNormal(std::vector <float> &nom,float x,float y,float z)
{
	nom.push_back(x);
	nom.push_back(y);
	nom.push_back(z);
}

void FsLazyWindowApplication::RemakeVertexArray(void)
{
	vtx.clear();
	nom.clear();
	col.clear();
	highDhaEdgeVtx.clear();

	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		auto plCol=mesh.GetColor(plHd);
		auto plNom=mesh.GetNormal(plHd);

		// Let's assume every polygon is a triangle for now.
		if(3==plVtHd.size())
		{
			for(int i=0; i<3; ++i)
			{
				auto vtPos=mesh.GetVertexPosition(plVtHd[i]);
				vtx.push_back(vtPos.xf());
				vtx.push_back(vtPos.yf());
				vtx.push_back(vtPos.zf());
				nom.push_back(plNom.xf());
				nom.push_back(plNom.yf());
				nom.push_back(plNom.zf());
				col.push_back(plCol.Rf());
				col.push_back(plCol.Gf());
				col.push_back(plCol.Bf());
				col.push_back(plCol.Af());
			}
		}

		auto nom=mesh.GetNormal(plHd);
		for(int i=0; i<plVtHd.size(); ++i)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,i);
			if(mesh.NullPolygon()!=neiPlHd)
			{
				auto neiNom=mesh.GetNormal(neiPlHd);
				if(nom*neiNom<cos(YsPi/4.0))
				{
					auto vtPos0=mesh.GetVertexPosition(plVtHd[i]);
					auto vtPos1=mesh.GetVertexPosition(plVtHd[(i+1)%plVtHd.size()]);
					highDhaEdgeVtx.push_back(vtPos0.x());
					highDhaEdgeVtx.push_back(vtPos0.y());
					highDhaEdgeVtx.push_back(vtPos0.z());
					highDhaEdgeVtx.push_back(vtPos1.x());
					highDhaEdgeVtx.push_back(vtPos1.y());
					highDhaEdgeVtx.push_back(vtPos1.z());
				}
			}
		}
	}
}

void FsLazyWindowApplication::RemakeDualVertexArray(void)
{
	dualVtx.clear();
	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		auto cen0=mesh.GetCenter(plHd);
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(int i=0; i<plVtHd.size(); ++i)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,i);
			if(mesh.NullPolygon()!=neiPlHd)
			{
				auto cen1=mesh.GetCenter(neiPlHd);

				dualVtx.push_back(cen0.xf());
				dualVtx.push_back(cen0.yf());
				dualVtx.push_back(cen0.zf());
				dualVtx.push_back(cen1.xf());
				dualVtx.push_back(cen1.yf());
				dualVtx.push_back(cen1.zf());
			}
		}
	}
}

YsMatrix4x4 FsLazyWindowApplication::GetProjection(void) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto aspect=(double)wid/(double)hei;
	return MakePerspective(45.0,aspect,d/10.0,d*2.0);
}

YsMatrix4x4 FsLazyWindowApplication::GetModelView(void) const
{
	YsMatrix4x4 globalToCamera=Rc;
	globalToCamera.Invert();

	YsMatrix4x4 modelView;
	modelView.Translate(0,0,-d);
	modelView*=globalToCamera;
	modelView.Translate(-t);
	return modelView;
}

YsShellExt::PolygonHandle FsLazyWindowApplication::PickedPlHd(int mx,int my) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto vp=WindowToViewPort(wid,hei,mx,my);

	auto perspective=GetProjection();
	auto modelView=GetModelView();

	YsMatrix4x4 all=perspective*modelView;
	all.Invert();

	auto nearPos=vp,farPos=vp;
	nearPos.SetZ(-1.0);
	farPos.SetZ(1.0);

	YsVec3 ln[2];
	all.Mul(ln[0],nearPos,1.0);
	all.Mul(ln[1],farPos,1.0);

	YsShellExt::PolygonHandle pickedPlHd=mesh.NullPolygon();
	double pickedZ=0.0;
	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		std::vector <YsVec3> plVtPos;
		for(auto vtHd : mesh.GetPolygonVertex(plHd))
		{
			plVtPos.push_back(mesh.GetVertexPosition(vtHd));
		}
		YsPlane pln;
		YsVec3 crs;
		if(YSOK==pln.MakeBestFitPlane(plVtPos) &&
		   YSOK==pln.GetPenetration(crs,ln[0],ln[1]) &&
		   YSINSIDE==YsCheckInsidePolygon3(crs,plVtPos))
		{
			crs=modelView*crs;
			if(mesh.NullPolygon()==pickedPlHd || crs.z()>pickedZ)
			{
				pickedPlHd=plHd;
				pickedZ=crs.z();
			}
		}
	}

	return pickedPlHd;
}

YsShellExt::VertexHandle FsLazyWindowApplication::PickedVtHd(int mx,int my,int pixRange) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto vp=WindowToViewPort(wid,hei,mx,my);

	auto projection=GetProjection();
	auto modelView=GetModelView();

	double pickedZ=0.0;
	auto pickedVtHd=mesh.NullVertex();
	for(auto vtHd=mesh.NullVertex(); true==mesh.MoveToNextVertex(vtHd); )
	{
		auto vtPos=mesh.GetVertexPosition(vtHd);
		vtPos=projection*modelView*vtPos;
		auto winPos=ViewPortToWindow(wid,hei,vtPos);
		int dx=(mx-winPos.x()),dy=(my-winPos.y());
		if(-pixRange<=dx && dx<=pixRange && -pixRange<=dy && dy<=pixRange)
		{
			if(mesh.NullVertex()==pickedVtHd || vtPos.z()<pickedZ)
			{
				pickedVtHd=vtHd;
				pickedZ=vtPos.z();
			}
		}
	}

	return pickedVtHd;
}

FsLazyWindowApplication::FsLazyWindowApplication()
{
	mode=NORMAL_MODE;

	needRedraw=false;
	d=10.0;
	t=YsVec3::Origin();

	lineOfLastPick[0]=YsVec3::Origin();
	lineOfLastPick[1]=YsVec3::Origin();
	lastPickedVtHd[0]=mesh.NullVertex();
	lastPickedVtHd[1]=mesh.NullVertex();
	lastPickedPlHd=mesh.NullPolygon();
}

/* virtual */ void FsLazyWindowApplication::BeforeEverything(int argc,char *argv[])
{
}
/* virtual */ void FsLazyWindowApplication::GetOpenWindowOption(FsOpenWindowOption &opt) const
{
	opt.x0=0;
	opt.y0=0;
	opt.wid=1200;
	opt.hei=800;
}
/* virtual */ void FsLazyWindowApplication::Initialize(int argc,char *argv[])
{
	if(2<=argc && true==mesh.LoadStl(argv[1]))
	{
		mesh.EnableSearch();

		simplifier.Start(mesh);

		RemakeVertexArray();
		mesh.GetBoundingBox(bbx[0],bbx[1]);

		t=(bbx[0]+bbx[1])/2.0;
		d=(bbx[1]-bbx[0]).GetLength()*1.2;

		printf("Target %s\n",t.Txt());
		printf("Diagonal %lf\n",d);
	}
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		SetMustTerminate(true);
	}

	// if(FSKEY_X==key && mesh.NullVertex()!=lastPickedVtHd)
	// {
	// 	auto vtPos=mesh.GetVertexPosition(lastPickedVtHd);
	// 	vtPos.AddX(1.0);
	// 	mesh.SetVertexPosition(lastPickedVtHd,vtPos);
	// 	RemakeVertexArray();
	// }

	if(FSKEY_Q==key)
	{
		int i=0;
		printf("Start with %d\n",(int)mesh.GetNumPolygon());
		auto n=mesh.GetNumPolygon();
		if(1000<n)
		{
			while(n-1000<mesh.GetNumPolygon())
			{
				if(0==i%100)
				{
					printf("%d\n",(int)mesh.GetNumPolygon());
				}
				++i;
				simplifier.SimplifyOneStep(mesh);
			}
		}
		printf("%d polygons\n",mesh.GetNumPolygon());
		RemakeVertexArray();
	}
	if(FSKEY_P==key && mesh.NullVertex()!=lastPickedVtHd[0] && mesh.NullVertex()!=lastPickedVtHd[1])
	{
		for(auto edPlHd : mesh.FindPolygonFromEdgePiece(lastPickedVtHd[0],lastPickedVtHd[1]))
		{
			mesh.SetPolygonColor(edPlHd,YsGreen());
		}
		RemakeVertexArray();
	}
	if(FSKEY_D==key)
	{
		if(mode==NORMAL_MODE)
		{
			mode=DUAL_MODE;
			RemakeDualVertexArray();
		}
		else
		{
			mode=NORMAL_MODE;
			RemakeVertexArray();
		}
	}
	if(FSKEY_M==key)
	{
		ColorMap(mesh);
		RemakeVertexArray();
	}
	if(FSKEY_L==key && mesh.NullPolygon()!=lastPickedPlHd)
	{
		for(auto connPlHd : GetConnectedPolygon(mesh,lastPickedPlHd))
		{
			mesh.SetPolygonColor(connPlHd,YsWhite());
		}
		RemakeVertexArray();
	}
	if(FSKEY_C==key)
	{
		if(nullptr!=lastPickedVtHd[0] && nullptr!=lastPickedVtHd[1])
		{
			CollapseEdge(mesh,lastPickedVtHd[0],lastPickedVtHd[1]);
			RemakeVertexArray();
		}
	}

	if(FsGetKeyState(FSKEY_LEFT))
	{
		Rc.RotateXZ(YsPi/60.0);
	}
	if(FsGetKeyState(FSKEY_RIGHT))
	{
		Rc.RotateXZ(-YsPi/60.0);
	}
	if(FsGetKeyState(FSKEY_UP))
	{
		Rc.RotateYZ(YsPi/60.0);
	}
	if(FsGetKeyState(FSKEY_DOWN))
	{
		Rc.RotateYZ(-YsPi/60.0);
	}


	int mx,my,lb,mb,rb;
	int evt=FsGetMouseEvent(lb,mb,rb,mx,my);
	if(FSMOUSEEVENT_LBUTTONDOWN==evt)
	{
		int wid,hei;
		FsGetWindowSize(wid,hei);
		auto vp=WindowToViewPort(wid,hei,mx,my);

		auto perspective=GetProjection();
		auto modelView=GetModelView();

		YsMatrix4x4 all=perspective*modelView;
		all.Invert();

		auto nearPos=vp,farPos=vp;
		nearPos.SetZ(-1.0);
		farPos.SetZ(1.0);

		all.Mul(lineOfLastPick[0],nearPos,1.0);
		all.Mul(lineOfLastPick[1],farPos,1.0);

		auto pickedVtHd=PickedVtHd(mx,my,8);
		if(mesh.NullVertex()!=pickedVtHd)
		{
			lastPickedVtHd[1]=lastPickedVtHd[0];
			lastPickedVtHd[0]=pickedVtHd;

			MeshLattice ltc;
			ltc.SetDomain(mesh,100,100,100);

			const double tol=0.000001;
			auto vtPos=mesh.GetVertexPosition(pickedVtHd);
			auto min=vtPos,max=vtPos;
			min-=YsVec3(tol,tol,tol);
			max+=YsVec3(tol,tol,tol);

			auto allVtHd=ltc.FindVertex(min,max);

			printf("%d duplicates\n",(int)allVtHd.size());

			auto connVtHd=GetNNeighbor(mesh,pickedVtHd,3);
			printf("%d connections\n",(int)connVtHd.size());

			highlightVtx.clear();
			for(auto vtHd : connVtHd)
			{
				auto vtPos=mesh.GetVertexPosition(vtHd);
				highlightVtx.push_back(vtPos.xf());
				highlightVtx.push_back(vtPos.yf());
				highlightVtx.push_back(vtPos.zf());
			}

			if(nullptr!=lastPickedVtHd[0] && nullptr!=lastPickedVtHd[1])
			{
				auto pathVtHd=GreedyPathSearch(mesh,lastPickedVtHd[0],lastPickedVtHd[1]);
				pathVtx.clear();
				for(auto vtHd : pathVtHd)
				{
					auto pos=mesh.GetVertexPosition(vtHd);
					pathVtx.push_back(pos.xf());
					pathVtx.push_back(pos.yf());
					pathVtx.push_back(pos.zf());
				}
			}
		}

		auto pickedPlHd=PickedPlHd(mx,my);
		if(mesh.NullPolygon()!=pickedPlHd)
		{
			lastPickedPlHd=pickedPlHd;
			mesh.SetPolygonColor(pickedPlHd,YsRed());
			RemakeVertexArray();
		}
	}


	needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
	needRedraw=false;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto aspect=(double)wid/(double)hei;
	glViewport(0,0,wid,hei);

	YsMatrix4x4 projection=GetProjection();
	GLfloat projectionGl[16];
	projection.GetOpenGlCompatibleMatrix(projectionGl);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(projectionGl);

	YsMatrix4x4 globalToCamera=Rc;
	globalToCamera.Invert();

	YsMatrix4x4 modelView=GetModelView();

	GLfloat modelViewGl[16];
	modelView.GetOpenGlCompatibleMatrix(modelViewGl);

	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat lightDir[]={0,1/sqrt(2.0f),1/sqrt(2.0f),0};
	glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMultMatrixf(modelViewGl);

	if(NORMAL_MODE==mode)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT,0,col.data());
		glNormalPointer(GL_FLOAT,0,nom.data());
		glVertexPointer(3,GL_FLOAT,0,vtx.data());
		glDrawArrays(GL_TRIANGLES,0,vtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glLineWidth(8);
		glDisable(GL_LIGHTING);
		glColor3ub(0,0,0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,highDhaEdgeVtx.data());
		glDrawArrays(GL_LINES,0,highDhaEdgeVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);

		glColor3ub(255,0,255);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,pathVtx.data());
		glDrawArrays(GL_LINE_STRIP,0,pathVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glColor3ub(0,0,0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,dualVtx.data());
		glDrawArrays(GL_LINES,0,dualVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
	}


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	const GLfloat lineVtx[6]=
	{
		lineOfLastPick[0].xf(),lineOfLastPick[0].yf(),lineOfLastPick[0].zf(),
		lineOfLastPick[1].xf(),lineOfLastPick[1].yf(),lineOfLastPick[1].zf(),
	};
	const GLfloat lineCol[8]=
	{
		1,0,0,1,0,0,1,1
	};
	glColorPointer(4,GL_FLOAT,0,lineCol);
	glVertexPointer(3,GL_FLOAT,0,lineVtx);
	glDrawArrays(GL_LINES,0,2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


	for(auto vtHd : lastPickedVtHd)
	{
		if(mesh.NullVertex()!=vtHd)
		{
			auto vtPos=mesh.GetVertexPosition(vtHd);
			GLfloat pointPos[3]={vtPos.xf(),vtPos.yf(),vtPos.zf()};
			GLfloat pointCol[4]={1.0f,0.0f,1.0f,1.0f};

			glDisable(GL_LIGHTING);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glPointSize(8);
			glVertexPointer(3,GL_FLOAT,0,pointPos);
			glColorPointer(4,GL_FLOAT,0,pointCol);
			glDrawArrays(GL_POINTS,0,1);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
		}
	}

	if(0<highlightVtx.size()/3)
	{
		glColor3ub(255,0,0);
		glDisable(GL_LIGHTING);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPointSize(4);
		glVertexPointer(3,GL_FLOAT,0,highlightVtx.data());
		glDrawArrays(GL_POINTS,0,highlightVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	FsSwapBuffers();
}
/* virtual */ bool FsLazyWindowApplication::UserWantToCloseProgram(void)
{
	return true; // Returning true will just close the program.
}
/* virtual */ bool FsLazyWindowApplication::MustTerminate(void) const
{
	return FsLazyWindowApplicationBase::MustTerminate();
}
/* virtual */ long long int FsLazyWindowApplication::GetMinimumSleepPerInterval(void) const
{
	return 10;
}
/* virtual */ void FsLazyWindowApplication::BeforeTerminate(void)
{
}
/* virtual */ bool FsLazyWindowApplication::NeedRedraw(void) const
{
	return needRedraw;
}


static FsLazyWindowApplication *appPtr=nullptr;

/* static */ FsLazyWindowApplicationBase *FsLazyWindowApplicationBase::GetApplication(void)
{
	if(nullptr==appPtr)
	{
		appPtr=new FsLazyWindowApplication;
	}
	return appPtr;
}
