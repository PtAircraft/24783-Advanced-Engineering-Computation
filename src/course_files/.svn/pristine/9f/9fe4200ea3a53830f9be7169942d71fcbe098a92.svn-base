#ifndef RENDERE_IS_INCLUDED
#define RENDERE_IS_INCLUDED
/* { */

#include <ysgl.h>
#include <stdio.h>
#include <vector>

std::vector <char> ReadTextFile(const char fn[]);


class RendererBase
{
public:
    GLuint programIdent;
    GLuint vertexShaderIdent,fragmentShaderIdent;

	bool CompileFile(const char vtxShaderFn[],const char fragShaderFn[]);
    bool Compile(const std::vector <char> &vtxShaderSource,const std::vector <char> &fragShaderSource);
protected:
    bool CompileShader(int shaderIdent);
    bool LinkShader(void);
    virtual void CacheAttributeAndUniformIdent(void)=0;
};

class PassThroughRenderer : public RendererBase
{
public:
    GLuint attribVertexPos;
    virtual void CacheAttributeAndUniformIdent(void);
};

class ColorAsAttributeRenderer : public RendererBase
{
public:
    GLuint attribVertexPos;
    GLuint attribColorPos;
    virtual void CacheAttributeAndUniformIdent(void);
};

class UniformColorRenderer : public RendererBase
{
public:
    GLuint attribVertexPos;
    GLuint uniformColorPos;
	virtual void CacheAttributeAndUniformIdent(void);
};

class Sampler2dRenderer : public RendererBase
{
public:
    GLuint attribVertexPos;
    GLuint attribTexCoordPos;
    GLuint uniformTexIdentPos;
    virtual void CacheAttributeAndUniformIdent(void);
};

class Plain3dRenderer : public RendererBase
{
public:
    GLuint attribVertexPos;
    GLuint attribColorPos;
    GLuint uniformProjectionPos;
    GLuint uniformModelViewPos;
    virtual void CacheAttributeAndUniformIdent(void);
};

/* } */
#endif
