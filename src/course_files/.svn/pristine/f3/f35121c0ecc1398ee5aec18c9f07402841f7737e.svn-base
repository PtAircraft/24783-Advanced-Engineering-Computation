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

#include "renderer.h"
#include "checker.h"

class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	bool needRedraw;
	PassThroughRenderer passThrough;
	ColorAsAttributeRenderer colorAsAttrib;
	UniformColorRenderer uniformColor;
	Sampler2dRenderer sampler2d;

	GLuint texIdent;

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

FsLazyWindowApplication::FsLazyWindowApplication()
{
	needRedraw=false;
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

	glGenTextures(1,&texIdent);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texIdent);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexImage2D(
	    GL_TEXTURE_2D,0,GL_RGBA,checker_pattern_wid,checker_pattern_hei,
	                  0,GL_RGBA,GL_UNSIGNED_BYTE,checker_pattern);


	std::vector <char> vtxShader,fragShader;
	vtxShader=ReadTextFile("passthrough_vertexShader.glsl");
	fragShader=ReadTextFile("red_fragmentShader.glsl");

	printf("%s\n",vtxShader.data());
	printf("%s\n",fragShader.data());

	passThrough.Compile(vtxShader,fragShader);

	colorAsAttrib.CompileFile("color_as_attribute_vertexShader.glsl","color_as_attribute_fragmentShader.glsl");

	uniformColor.CompileFile("uniform_color_vertexShader.glsl","uniform_color_fragmentShader.glsl");

	sampler2d.CompileFile("sampler2d_vertexShader.glsl","sampler2d_fragmentShader.glsl");
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		SetMustTerminate(true);
	}
	needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

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
    const GLfloat col[16]=
    {
		1.0f,0.0f,0.0f,1.0f,
		0.0f,1.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,1.0f,
		1.0f,1.0f,0.0f,0.0f
	};
    glEnableVertexAttribArray(sampler2d.attribVertexPos);
    glVertexAttribPointer(sampler2d.attribVertexPos,3,GL_FLOAT,GL_FALSE,0,vtx);

    glEnableVertexAttribArray(sampler2d.attribTexCoordPos);
    glVertexAttribPointer(sampler2d.attribTexCoordPos,2,GL_FLOAT,GL_FALSE,0,texCoord);

	glUniform1i(sampler2d.uniformTexIdentPos,0);

    glDrawArrays(GL_TRIANGLE_FAN,0,4);

    glDisableVertexAttribArray(sampler2d.attribVertexPos);
    glDisableVertexAttribArray(sampler2d.attribTexCoordPos);

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
