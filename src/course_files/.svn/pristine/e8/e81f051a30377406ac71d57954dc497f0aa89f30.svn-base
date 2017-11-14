#include "renderer.h"

std::vector <char> ReadTextFile(const char fn[])
{
	std::vector <char> txt;
	FILE *fp=fopen(fn,"r");
	if(nullptr!=fp)
	{
		char str[256];
		while(nullptr!=fgets(str,255,fp))
		{
			for(int i=0; 0!=str[i]; ++i)
			{
				txt.push_back(str[i]);
			}
		}
		fclose(fp);
	}
	txt.push_back(0);
	return txt;
}

bool RendererBase::Compile(
    const std::vector <char> &vtxShaderSource,
    const std::vector <char> &fragShaderSource)
{
    bool res=true;

    vertexShaderIdent=glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderIdent=glCreateShader(GL_FRAGMENT_SHADER);
    programIdent=glCreateProgram();

    const char *vtxShaderSourcePtr=vtxShaderSource.data();
    const char *fragShaderSourcePtr=fragShaderSource.data();
    glShaderSource(vertexShaderIdent,1,&vtxShaderSourcePtr,NULL);
    glShaderSource(fragmentShaderIdent,1,&fragShaderSourcePtr,NULL);

    if(true!=CompileShader(vertexShaderIdent))
    {
        res=false;
    }
    if(true!=CompileShader(fragmentShaderIdent))
    {
        res=false;
    }
    if(true!=LinkShader())
    {
        res=false;
    }

    CacheAttributeAndUniformIdent();

    return res;
}

bool RendererBase::CompileFile(const char vtxShaderFn[],const char fragShaderFn[])
{
    auto vtxShaderSource=ReadTextFile(vtxShaderFn);
    auto fragShaderSource=ReadTextFile(fragShaderFn);

    printf("Vertex Shader\n");
    printf("%s\n",vtxShaderSource.data());

    printf("Fragment Shader\n");
    printf("%s\n",fragShaderSource.data());

    return Compile(vtxShaderSource,fragShaderSource);
}

bool RendererBase::CompileShader(int shaderIdent)
{
    int compileSta=99999,infoLogLength=99999,acquiredErrMsgLen=99999;
    int linkSta=99999;
    const int errMsgLen=1024;
    char errMsg[1024];

    glCompileShader(shaderIdent);

    glGetShaderiv(shaderIdent,GL_COMPILE_STATUS,&compileSta);
    glGetShaderiv(shaderIdent,GL_INFO_LOG_LENGTH,&infoLogLength);
    glGetShaderInfoLog(shaderIdent,errMsgLen-1,&acquiredErrMsgLen,errMsg);
    printf("Compile Status %d Info Log Length %d Error Message Length %d\n",
        compileSta,infoLogLength,acquiredErrMsgLen);

    if(GL_TRUE!=compileSta)
    {
	    printf("Error Message: \n%s\n",errMsg);
        return false;
    }
    return true;
}

bool RendererBase::LinkShader(void)
{
    int compileSta=99999,infoLogLength=99999,acquiredErrMsgLen=99999;
    int linkSta=99999;
    const int errMsgLen=1024;
    char errMsg[1024];

	glBindAttribLocation(programIdent,0,"vertex");

    glAttachShader(programIdent,vertexShaderIdent);
    glAttachShader(programIdent,fragmentShaderIdent);
    glLinkProgram(programIdent);
    glGetProgramiv(programIdent,GL_LINK_STATUS,&linkSta);
    glGetProgramiv(programIdent,GL_INFO_LOG_LENGTH,&infoLogLength);
    glGetProgramInfoLog(programIdent,errMsgLen-1,&acquiredErrMsgLen,errMsg);
    printf("Link Status %d Info Log Length %d Error Message Length %d\n",
        linkSta,infoLogLength,acquiredErrMsgLen);

    if(GL_TRUE!=linkSta)
    {
        printf("Error Message: \n%s\n",errMsg);
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////

void PassThroughRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    printf("Attribute Vertex Position=%d\n",attribVertexPos);
}

////////////////////////////////////////////////////////////

void ColorAsAttributeRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    attribColorPos=glGetAttribLocation(programIdent,"color");
    printf("Attribute Vertex Position=%d\n",attribVertexPos);
}

////////////////////////////////////////////////////////////

/* virtual */ void UniformColorRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    uniformColorPos=glGetUniformLocation(programIdent,"color");
    printf("Attribute Vertex Position=%d\n",attribVertexPos);
}

////////////////////////////////////////////////////////////

void Sampler2dRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    printf("Attribute Vertex Position=%d\n",attribVertexPos);
    attribTexCoordPos=glGetAttribLocation(programIdent,"texCoord");
    printf("Attribute TexCoord Position=%d\n",attribTexCoordPos);
    uniformTexIdentPos=glGetUniformLocation(programIdent,"texIdent");
    printf("Uniform TexIdent Position=%d\n",uniformTexIdentPos);
}

////////////////////////////////////////////////////////////

void Plain3dRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    printf("Attribute Vertex Position=%d\n",attribVertexPos);
    attribColorPos=glGetAttribLocation(programIdent,"color");
    printf("Attribute Color Position=%d\n",attribColorPos);

    uniformProjectionPos=glGetUniformLocation(programIdent,"projection");
    printf("Uniform Projection Position=%d\n",uniformProjectionPos);
    uniformModelViewPos=glGetUniformLocation(programIdent,"modelView");
    printf("Uniform ModelView Position=%d\n",uniformModelViewPos);
}

////////////////////////////////////////////////////////////

void Gouraud3dRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    attribNormalPos=glGetAttribLocation(programIdent,"normal");
    attribColorPos=glGetAttribLocation(programIdent,"color");

    uniformProjectionPos=glGetUniformLocation(programIdent,"projection");
    uniformModelViewPos=glGetUniformLocation(programIdent,"modelView");
    uniformLightDirPos=glGetUniformLocation(programIdent,"lightDir");
    uniformAmbientPos=glGetUniformLocation(programIdent,"ambient");
    uniformSpecularIntensityPos=glGetUniformLocation(programIdent,"specularIntensity");
    uniformSpecularExponentPos=glGetUniformLocation(programIdent,"specularExponent");
}

////////////////////////////////////////////////////////////

void Billboard3dRenderer::CacheAttributeAndUniformIdent(void)
{
    attribVertexPos=glGetAttribLocation(programIdent,"vertex");
    printf("attribVertexPos=%d\n",attribVertexPos);
    attribOffsetPos=glGetAttribLocation(programIdent,"offset");
    printf("attribOffsetPos=%d\n",attribOffsetPos);
    attribColorPos=glGetAttribLocation(programIdent,"color");
    printf("attribColorPos=%d\n",attribColorPos);
    attribTexCoordPos=glGetAttribLocation(programIdent,"texCoord");
    printf("attribTexCoordPos=%d\n",attribTexCoordPos);

    uniformProjectionPos=glGetUniformLocation(programIdent,"projection");
    printf("uniformProjectionPos=%d\n",uniformProjectionPos);
    uniformModelViewPos=glGetUniformLocation(programIdent,"modelView");
    printf("uniformModelViewPos=%d\n",uniformModelViewPos);
    uniformOffsetInViewPos=glGetUniformLocation(programIdent,"offsetInView");
    printf("uniformOffsetInViewPos=%d\n",uniformOffsetInViewPos);
    uniformOffsetInPixelPos=glGetUniformLocation(programIdent,"offsetInPixel");
    printf("uniformOffsetInPixelPos=%d\n",uniformOffsetInPixelPos);
    uniformViewportWidthPos=glGetUniformLocation(programIdent,"viewportWidth");
    printf("uniformViewportWidthPos=%d\n",uniformViewportWidthPos);
    uniformViewportHeightPos=glGetUniformLocation(programIdent,"viewportHeight");
    printf("uniformViewportHeightPos=%d\n",uniformViewportHeightPos);
    uniformTexture2dPos=glGetUniformLocation(programIdent,"texture2d");
    printf("uniformTexture2dPos=%d\n",uniformTexture2dPos);
}
