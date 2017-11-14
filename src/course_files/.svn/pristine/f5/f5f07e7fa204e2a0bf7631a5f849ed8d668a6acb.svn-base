#include <vector>

#include <ysclass.h>
#include <polygonalmesh.h>

#include <fslazywindow.h>

#include "glutil.h"


class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	bool needRedraw;

	YsMatrix4x4 Rc;
	double d;
	YsVec3 t;

	YsVec3 lastClickedLine[2];
	PolygonalMesh mesh;
	std::vector <GLfloat> vtxAry,nomAry,colAry;

	static void MakeCubeVertexArray(
	    std::vector <GLfloat> &vtx,
	    std::vector <GLfloat> &nom,
	    std::vector <GLfloat> &col,
	    float x1,float y1,float z1,float x2,float y2,float z2);
	static void AddVertex(std::vector <GLfloat> &vtx,GLfloat x,GLfloat y,GLfloat z);
	static void AddNormal(std::vector <GLfloat> &nom,GLfloat x,GLfloat y,GLfloat z);
	static void AddColor(std::vector <GLfloat> &vtx,GLfloat r,GLfloat g,GLfloat b,GLfloat a);

	void RemakeVertexArray(void);
	void SetUpHeadLight(void);
	void MouseToLine(YsVec3 ln[2],int mx,int my);
	YsMatrix4x4 GetProjection(void) const;
	YsMatrix4x4 GetModelView(void) const;

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

void FsLazyWindowApplication::RemakeVertexArray(void)
{
	vtxAry.clear();
	nomAry.clear();
	colAry.clear();

	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		auto nom=mesh.GetNormal(plHd);
		auto col=mesh.GetColor(plHd);
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		if(3==plVtHd.size())
		{
			for(auto vtHd : plVtHd)
			{
				auto vtPos=mesh.GetVertexPosition(vtHd);
				vtxAry.push_back(vtPos.xf());
				vtxAry.push_back(vtPos.yf());
				vtxAry.push_back(vtPos.zf());

				nomAry.push_back(nom.xf());
				nomAry.push_back(nom.yf());
				nomAry.push_back(nom.zf());

				colAry.push_back(col.Rf());
				colAry.push_back(col.Gf());
				colAry.push_back(col.Bf());
				colAry.push_back(col.Af());
			}
		}
	}
}

void FsLazyWindowApplication::MakeCubeVertexArray(
	    std::vector <GLfloat> &vtx,
	    std::vector <GLfloat> &nom,
	    std::vector <GLfloat> &col,
	    float x1,float y1,float z1,float x2,float y2,float z2)
{
	vtx.clear();
	nom.clear();
	col.clear();

	glEnable(GL_NORMALIZE);

    AddVertex(vtx,x1,y1,z1);AddColor(col,0,0,1,1);AddNormal(nom,0,0,-1);
    AddVertex(vtx,x2,y1,z1);AddColor(col,0,0,1,1);AddNormal(nom,0,0,-1);
    AddVertex(vtx,x2,y2,z1);AddColor(col,0,0,1,1);AddNormal(nom,0,0,-1);
    AddVertex(vtx,x1,y2,z1);AddColor(col,0,0,1,1);AddNormal(nom,0,0,-1);

	AddVertex(vtx,x1,y1,z2);AddColor(col,0,1,0,1);AddNormal(nom,0,0,1);
	AddVertex(vtx,x2,y1,z2);AddColor(col,0,1,0,1);AddNormal(nom,0,0,1);
	AddVertex(vtx,x2,y2,z2);AddColor(col,0,1,0,1);AddNormal(nom,0,0,1);
	AddVertex(vtx,x1,y2,z2);AddColor(col,0,1,0,1);AddNormal(nom,0,0,1);

    AddVertex(vtx,x1,y1,z1);AddColor(col,0,1,1,1);AddNormal(nom,0,-1,0);
    AddVertex(vtx,x2,y1,z1);AddColor(col,0,1,1,1);AddNormal(nom,0,-1,0);
    AddVertex(vtx,x2,y1,z2);AddColor(col,0,1,1,1);AddNormal(nom,0,-1,0);
    AddVertex(vtx,x1,y1,z2);AddColor(col,0,1,1,1);AddNormal(nom,0,-1,0);

    AddVertex(vtx,x1,y2,z1);AddColor(col,1,0,0,1);AddNormal(nom,0,1,0);
    AddVertex(vtx,x2,y2,z1);AddColor(col,1,0,0,1);AddNormal(nom,0,1,0);
    AddVertex(vtx,x2,y2,z2);AddColor(col,1,0,0,1);AddNormal(nom,0,1,0);
    AddVertex(vtx,x1,y2,z2);AddColor(col,1,0,0,1);AddNormal(nom,0,1,0);

    
    AddVertex(vtx,x1,y1,z1);AddColor(col,1,0,1,1);AddNormal(nom,-1,0,0);
    AddVertex(vtx,x1,y2,z1);AddColor(col,1,0,1,1);AddNormal(nom,-1,0,0);
    AddVertex(vtx,x1,y2,z2);AddColor(col,1,0,1,1);AddNormal(nom,-1,0,0);
    AddVertex(vtx,x1,y1,z2);AddColor(col,1,0,1,1);AddNormal(nom,-1,0,0);

    
    AddVertex(vtx,x2,y1,z1);AddColor(col,1,1,0,1);AddNormal(nom,1,0,0);
    AddVertex(vtx,x2,y2,z1);AddColor(col,1,1,0,1);AddNormal(nom,1,0,0);
    AddVertex(vtx,x2,y2,z2);AddColor(col,1,1,0,1);AddNormal(nom,1,0,0);
    AddVertex(vtx,x2,y1,z2);AddColor(col,1,1,0,1);AddNormal(nom,1,0,0);
}
/* static */ void FsLazyWindowApplication::AddVertex(std::vector <GLfloat> &vtx,GLfloat x,GLfloat y,GLfloat z)
{
	vtx.push_back(x);
	vtx.push_back(y);
	vtx.push_back(z);
}
/* static */ void FsLazyWindowApplication::AddNormal(std::vector <GLfloat> &nom,GLfloat x,GLfloat y,GLfloat z)
{
	nom.push_back(x);
	nom.push_back(y);
	nom.push_back(z);
}
/* static */ void FsLazyWindowApplication::AddColor(std::vector <GLfloat> &col,GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	col.push_back(r);
	col.push_back(g);
	col.push_back(b);
	col.push_back(a);
}


FsLazyWindowApplication::FsLazyWindowApplication()
{
	needRedraw=false;

	d=10.0;
	t.Set(0.0,0.0,0.0);  // t=YsVec3::Origin();

	lastClickedLine[0]=YsVec3::Origin();
	lastClickedLine[1]=YsVec3::Origin();
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
	if(2<=argc && true==mesh.LoadBinStl(argv[1]))
	{
		YsVec3 min,max;
		mesh.GetBoundingBox(min,max);
		printf("%lf %lf %lf\n",min.x(),min.y(),min.z());
		printf("%lf %lf %lf\n",max.x(),max.y(),max.z());

		d=(max-min).GetLength()*1.3;
		t=(min+max)/2.0;

		RemakeVertexArray();

		printf("%lf\n",d);
		printf("%lf %lf %lf\n",t.x(),t.y(),t.z());
	}
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		SetMustTerminate(true);
	}

	if(FsGetKeyState(FSKEY_LEFT))
	{
		Rc.RotateXZ(YsPi/180.0);
	}
	if(FsGetKeyState(FSKEY_RIGHT))
	{
		Rc.RotateXZ(-YsPi/180.0);
	}
	if(FsGetKeyState(FSKEY_UP))
	{
		Rc.RotateYZ(YsPi/180.0);
	}
	if(FsGetKeyState(FSKEY_DOWN))
	{
		Rc.RotateYZ(-YsPi/180.0);
	}

	int lb,mb,rb,mx,my;
	if(FSMOUSEEVENT_LBUTTONDOWN==FsGetMouseEvent(lb,mb,rb,mx,my))
	{
		MouseToLine(lastClickedLine,mx,my);
	}

	needRedraw=true;
}

void FsLazyWindowApplication::SetUpHeadLight(void)
{
    GLfloat lightDir[]={0,1/sqrt(2.0f),1/sqrt(2.0f),0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void FsLazyWindowApplication::MouseToLine(YsVec3 ln[2],int mx,int my)
{
    int wid,hei;
    FsGetWindowSize(wid,hei);
	YsVec3 viewCoord=WindowToViewPort(wid,hei,mx,my);

	YsVec3 nearPos=viewCoord,farPos=viewCoord;
	nearPos.SetZ(-1.0);
	farPos.SetZ(1.0);

	auto proj=GetProjection();
	auto modelView=GetModelView();

	proj.Invert();
	modelView.Invert();

	ln[0]=modelView*proj*nearPos;
	ln[1]=modelView*proj*farPos;
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
	YsMatrix4x4 modelView;

	modelView.Translate(0,0,-d);

	auto invRc=Rc;
	invRc.Invert();
	modelView*=invRc;

	modelView.Translate(-t);

	return modelView;
}

/* virtual */ void FsLazyWindowApplication::Draw(void)
{
	needRedraw=false;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    int wid,hei;
    FsGetWindowSize(wid,hei);
    glViewport(0,0,wid,hei);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	auto projection=GetProjection();
	GLfloat projectionGl[16];
	projection.GetOpenGlCompatibleMatrix(projectionGl);
	glMultMatrixf(projectionGl);


    YsMatrix4x4 modelView=GetModelView();

    GLfloat modelViewGl[16];
    modelView.GetOpenGlCompatibleMatrix(modelViewGl);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	SetUpHeadLight();

    glMultMatrixf(modelViewGl);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,colAry.data());
	glNormalPointer(GL_FLOAT,0,nomAry.data());
	glVertexPointer(3,GL_FLOAT,0,vtxAry.data());
	glDrawArrays(GL_TRIANGLES,0,vtxAry.size()/3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


	GLfloat lineColAry[8]=
	{
		0.0f,0.0f,1.0f,1.0f,
		0.0f,0.0f,1.0f,1.0f,
	};
	GLfloat lineVtxAry[6]=
	{
		lastClickedLine[0].xf(),lastClickedLine[0].yf(),lastClickedLine[0].zf(),
		lastClickedLine[1].xf(),lastClickedLine[1].yf(),lastClickedLine[1].zf(),
	};
	glDisable(GL_LIGHTING);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,lineColAry);
	glVertexPointer(3,GL_FLOAT,0,lineVtxAry);
	glDrawArrays(GL_LINES,0,2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


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
