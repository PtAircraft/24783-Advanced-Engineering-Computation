/* ////////////////////////////////////////////////////////////

File Name: main.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <vector>
#include <fslazywindow.h>
#include <ysgl.h>
#include <ysbitmap.h>

#include <ysshellext.h>


#include "renderer.h"
#include "checker.h"
#include "glutil.h"


class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	bool needRedraw;
	PassThroughRenderer passThrough;
	ColorAsAttributeRenderer colorAsAttrib;
	UniformColorRenderer uniformColor;
	Sampler2dRenderer sampler2d;
	Plain3dRenderer plain3d;
	Gouraud3dRenderer gouraud3d;
	Phong3dRenderer phong3d;
	Billboard3dRenderer billboard3d;
	ProgramPointSize3dRenderer programPointSize3d;

	GLuint texIdent;
	YsBitmap bmp;

	YsMatrix4x4 Rc;
	double d;
	YsVec3 t;

	YsShellExt mesh;
	std::vector <float> vtx,nom,col;
	YsVec3 bbx[2];

	void RemakeVertexArray(void);
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

void FsLazyWindowApplication::RemakeVertexArray(void)
{
	vtx.clear();
	nom.clear();
	col.clear();

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
	needRedraw=false;

	d=10.0;
	t=YsVec3::Origin();
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
	FsChangeToProgramDir();


	t=YsVec3::Origin();
	d=30.0;

	glGenTextures(1,&texIdent);

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texIdent);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexImage2D(
	    GL_TEXTURE_2D,0,GL_RGBA,checker_pattern_wid,checker_pattern_hei,
	                  0,GL_RGBA,GL_UNSIGNED_BYTE,checker_pattern); */

    YsBitmap bmp;
    if(YSOK==bmp.LoadPng("BabyBlueJay.png"))
    {
        printf("Texture Loaded.\n");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texIdent);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
            bmp.GetWidth(),bmp.GetHeight(),0,
            GL_RGBA,GL_UNSIGNED_BYTE,bmp.GetRGBABitmapPointer());
    }



	std::vector <char> vtxShader,fragShader;
	vtxShader=ReadTextFile("passthrough_vertexShader.glsl");
	fragShader=ReadTextFile("red_fragmentShader.glsl");

	printf("%s\n",vtxShader.data());
	printf("%s\n",fragShader.data());

	passThrough.Compile(vtxShader,fragShader);

	colorAsAttrib.CompileFile("color_as_attribute_vertexShader.glsl","color_as_attribute_fragmentShader.glsl");

	uniformColor.CompileFile("uniform_color_vertexShader.glsl","uniform_color_fragmentShader.glsl");

	sampler2d.CompileFile("sampler2d_vertexShader.glsl","sampler2d_fragmentShader.glsl");

	plain3d.CompileFile("plain3d_vertexShader.glsl","plain3d_fragmentShader.glsl");

	gouraud3d.CompileFile("gouroud3d_vertexShader.glsl","gouroud3d_fragmentShader.glsl");

	phong3d.CompileFile("phong3d_vertexShader.glsl","phong3d_fragmentShader.glsl");

	billboard3d.CompileFile("billboard3d_vertexShader.glsl","billboard3d_fragmentShader.glsl");

	programPointSize3d.CompileFile("program_point_size_vertexShader.glsl","program_point_size_fragmentShader.glsl");
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

	needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	int wid,hei;
	FsGetWindowSize(wid,hei);
	glViewport(0,0,wid,hei);


////////////////////////////////////////////////////////////
	{
	    glUseProgram(sampler2d.programIdent);
	    const GLfloat vtx[12]=
	    {
	       // -0.5f,-0.5f,0.0f,
	       //  0.5f,-0.5f,0.0f,
	       //  0.5f, 0.5f,0.0f,
	       // -0.5f, 0.5f,0.0f

			 0.0f,-0.5f, 0.0f,
			 0.5f, 0.0f, 0.0f,
			 0.0f, 0.5f, 0.0f,
			-0.5f, 0.0f, 0.0f,
	    };
	    const GLfloat texCoord[8]=
	    {
			0.0f,0.0f,
			1.0f,0.0f,
			1.0f,1.0f,
			0.0f,1.0f
		};
	    glEnableVertexAttribArray(sampler2d.attribVertexPos);
	    glVertexAttribPointer(sampler2d.attribVertexPos,3,GL_FLOAT,GL_FALSE,0,vtx);

	    glEnableVertexAttribArray(sampler2d.attribTexCoordPos);
	    glVertexAttribPointer(sampler2d.attribTexCoordPos,2,GL_FLOAT,GL_FALSE,0,texCoord);

		glUniform1i(sampler2d.uniformTexIdentPos,0);

	    glDrawArrays(GL_TRIANGLE_FAN,0,4);

	    glDisableVertexAttribArray(sampler2d.attribVertexPos);
	    glDisableVertexAttribArray(sampler2d.attribTexCoordPos);
	}
////////////////////////////////////////////////////////////


    glClear(GL_DEPTH_BUFFER_BIT);

	YsMatrix4x4 projection=GetProjection();
	GLfloat projectionGl[16];
	projection.GetOpenGlCompatibleMatrix(projectionGl);

	YsMatrix4x4 modelView=GetModelView();
	GLfloat modelViewGl[16];
	modelView.GetOpenGlCompatibleMatrix(modelViewGl);



	glUseProgram(plain3d.programIdent);
	glUniformMatrix4fv(plain3d.uniformProjectionPos,1,GL_FALSE,projectionGl);
	glUniformMatrix4fv(plain3d.uniformModelViewPos,1,GL_FALSE,modelViewGl);
	{
		GLfloat cubeEdgeVtx[]=
	    {
	        -10,-10,-10,  10,-10,-10,
	         10,-10,-10,  10,-10, 10,
	         10,-10, 10, -10,-10, 10,
	        -10,-10, 10, -10,-10,-10,

	        -10, 10,-10,  10, 10,-10,
	         10, 10,-10,  10, 10, 10,
	         10, 10, 10, -10, 10, 10,
	        -10, 10, 10, -10, 10,-10,

	        -10, 10,-10, -10,-10,-10,
	         10, 10,-10,  10,-10,-10,
	         10, 10, 10,  10,-10, 10,
	        -10, 10, 10, -10,-10, 10,
	    };
	    GLfloat cubeEdgeColor[]=
	    {
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,

	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,

	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	        0,0,0,1, 0,0,0,1,
	    };

	    glEnableVertexAttribArray(plain3d.attribVertexPos);
	    glVertexAttribPointer(plain3d.attribVertexPos,3,GL_FLOAT,GL_FALSE,0,cubeEdgeVtx);
	    glEnableVertexAttribArray(plain3d.attribColorPos);
	    glVertexAttribPointer(plain3d.attribColorPos,4,GL_FLOAT,GL_FALSE,0,cubeEdgeColor);

	    glDrawArrays(GL_LINES,0,24);

	    glDisableVertexAttribArray(plain3d.attribVertexPos);
	    glDisableVertexAttribArray(plain3d.attribColorPos);
	}

	{
		GLfloat billboardVtx[]=
	    {
	        -10,-10,-10,
	        -10,-10,-10,
	        -10,-10,-10,
	    };
	    GLfloat billboardOffset[]=
	    {
	        -1.0,-1.0,
	         3.0,-1.0,
	        -1.0, 3.0,
	    };
	    GLfloat billboardTexCoord[]=
	    {
	         0.0, 0.0,
	         2.0, 0.0,
	         0.0, 2.0,
	    };
	    GLfloat billboardColor[]=
	    {
	        1,1,1,1,
	        1,1,1,1,
	        1,1,1,1,
	    };

	    glUseProgram(billboard3d.programIdent);
	    glUniformMatrix4fv(billboard3d.uniformProjectionPos,1,GL_FALSE,projectionGl);
	    glUniformMatrix4fv(billboard3d.uniformModelViewPos,1,GL_FALSE,modelViewGl);

		glUniform1i(billboard3d.uniformTexture2dPos,0);

	    glUniform1f(billboard3d.uniformOffsetInViewPos,1.0f);
	    glUniform1f(billboard3d.uniformOffsetInPixelPos,0.0f);
	    glUniform1f(billboard3d.uniformViewportWidthPos,(GLfloat)wid);
	    glUniform1f(billboard3d.uniformViewportHeightPos,(GLfloat)hei);

	    glEnableVertexAttribArray(billboard3d.attribVertexPos);
	    glEnableVertexAttribArray(billboard3d.attribColorPos);
	    glEnableVertexAttribArray(billboard3d.attribTexCoordPos);
	    glEnableVertexAttribArray(billboard3d.attribOffsetPos);

	    glVertexAttribPointer(
	        billboard3d.attribVertexPos,3,GL_FLOAT,GL_FALSE,0,billboardVtx);
	    glVertexAttribPointer(
	        billboard3d.attribColorPos,4,GL_FLOAT,GL_FALSE,0,billboardColor);
	    glVertexAttribPointer(
	        billboard3d.attribTexCoordPos,2,GL_FLOAT,GL_FALSE,0,billboardTexCoord);
	    glVertexAttribPointer(
	        billboard3d.attribOffsetPos,2,GL_FLOAT,GL_FALSE,0,billboardOffset);

	    glDrawArrays(GL_TRIANGLES,0,3);

	    glDisableVertexAttribArray(billboard3d.attribVertexPos);
	    glDisableVertexAttribArray(billboard3d.attribColorPos);
	    glDisableVertexAttribArray(billboard3d.attribTexCoordPos);
	    glDisableVertexAttribArray(billboard3d.attribOffsetPos);
	}

	{
	    GLfloat quadVtx[12]=
	        {-10,-10, 10,   10,-10, 10,   10, 10, 10,  -10, 10, 10,};
	    GLfloat quadCol[16]=
	        {1,0,0,1,  0,1,0,1,  0,0,1,1,  1,0,1,1};
	    GLfloat quadPointSize[4]=
	        {1,2,3,4};
	    glUseProgram(programPointSize3d.programIdent);
	    glUniformMatrix4fv(programPointSize3d.uniformProjectionPos,1,GL_FALSE,projectionGl);
	    glUniformMatrix4fv(programPointSize3d.uniformModelViewPos,1,GL_FALSE,modelViewGl);

	    glUniform1f(programPointSize3d.uniformSizeInPixelPos,0.0f);
	    glUniform1f(programPointSize3d.uniformSizeIn3dPos,1.0f);
	    glUniform1f(programPointSize3d.uniformViewportHeightPos,(float)hei);


	    glEnableVertexAttribArray(programPointSize3d.attribVertexPos);
	    glEnableVertexAttribArray(programPointSize3d.attribColorPos);
	    glEnableVertexAttribArray(programPointSize3d.attribPointSizePos);

	    glVertexAttribPointer(programPointSize3d.attribVertexPos,3,GL_FLOAT,GL_FALSE,0,quadVtx);
	    glVertexAttribPointer(programPointSize3d.attribColorPos,4,GL_FLOAT,GL_FALSE,0,quadCol);
	    glVertexAttribPointer(programPointSize3d.attribPointSizePos,1,GL_FLOAT,GL_FALSE,0,quadPointSize);

	    glEnable(GL_PROGRAM_POINT_SIZE);
	    glDrawArrays(GL_POINTS,0,4);
	    glDisable(GL_PROGRAM_POINT_SIZE);

	    glDisableVertexAttribArray(programPointSize3d.attribVertexPos);
	    glDisableVertexAttribArray(programPointSize3d.attribColorPos);
	}

    FsSwapBuffers();


	needRedraw=false;
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
