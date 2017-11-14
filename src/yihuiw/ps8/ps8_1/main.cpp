#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <fslazywindow.h>
#include "renderer.h"
#include <ysgl.h>

using namespace std;
class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
    bool needRedraw;
    Plain2dRenderer p2r;
    GLuint texIdent;
    
    void PhysicalCoordToScreenCoord(int &sx,int &sy,double px,double py)
    {
        sx=(int)(px*10.0);
        sy=600-(int)(py*10.0);
    }
    
    void DrawCircle(int cx,int cy,int rad,int fill)
    {
        const double YS_PI=3.1415927;
        
        glUseProgram(p2r.programIdent);
        
        
        std::vector<GLfloat> vtx;
        int i;
        for(i=0; i<64; i++)
        {
            double angle=(double)i*YS_PI/32.0;
            double x=(double)cx+cos(angle)*(double)rad;
            double y=(double)cy+sin(angle)*(double)rad;
            vtx.push_back(x);
            vtx.push_back(y);
        }
        glEnableVertexAttribArray(p2r.attribVertexPos);
        glVertexAttribPointer(p2r.attribVertexPos,2,GL_FLOAT,GL_FALSE,0,vtx.data());
        if(0!=fill)
        {
            glDrawArrays(GL_POLYGON,0,64);
        }
        else
        {
            glDrawArrays(GL_LINE_LOOP,0,64);
        }
        glDisableVertexAttribArray(p2r.attribVertexPos);
        
    }
    
    void DrawRect(int x1,int y1,int x2,int y2,int fill)
    {
        glUseProgram(p2r.programIdent);
        
        std::vector<GLfloat> vtx;
        vtx.push_back(x1);
        vtx.push_back(y1);
        vtx.push_back(x2);
        vtx.push_back(y1);
        vtx.push_back(x2);
        vtx.push_back(y2);
        vtx.push_back(x1);
        vtx.push_back(y2);
        glEnableVertexAttribArray(p2r.attribVertexPos);
        glVertexAttribPointer(p2r.attribVertexPos,2,GL_FLOAT,GL_FALSE,0,vtx.data());
        
        if(0!=fill)
        {
            glDrawArrays(GL_QUADS,0,4);
        }
        else
        {
            glDrawArrays(GL_LINE_LOOP,0,4);
        }
        glDisableVertexAttribArray(p2r.attribVertexPos);
        
    }
    
    void DrawLine(int x1,int y1,int x2,int y2)
    {
        
        glUseProgram(p2r.programIdent);
        
        std::vector<GLfloat> vtx;
        vtx.push_back(x1);
        vtx.push_back(y1);
        vtx.push_back(x2);
        vtx.push_back(y2);
        glEnableVertexAttribArray(p2r.attribVertexPos);
        glVertexAttribPointer(p2r.attribVertexPos,2,GL_FLOAT,GL_FALSE,0,vtx.data());
        glDrawArrays(GL_LINES,0,2);
        glDisableVertexAttribArray(p2r.attribVertexPos);
        
    }
    
    int CheckHitTarget(
                       double missileX,double missileY,
                       double targetX,double targetY,double targetSizeX,double targetSizeY)
    {
        int relativeX,relativeY;
        relativeX=missileX-targetX;
        relativeY=missileY-targetY;
        if(0<=relativeX && relativeX<targetSizeX && 0<=relativeY && relativeY<targetSizeY)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    void DrawArtillery(double x,double y,double angle)
    {
        int sx,sy;
        PhysicalCoordToScreenCoord(sx,sy,x,y);
        //        };
        std::vector<GLfloat> col;
        for (int i = 0; i<4; i++)
        {
            col.push_back(0.0f);
            col.push_back(0.0f);
            col.push_back(1.0f);
            col.push_back(0.0f);
        }
        glEnableVertexAttribArray(p2r.attribColorPos);
        
        glVertexAttribPointer(p2r.attribColorPos,4,GL_FLOAT,GL_FALSE,0,col.data());
        
        DrawRect(sx-5,sy-5,sx+5,sy+5,1);
        glDisableVertexAttribArray(p2r.attribColorPos);
        int vx,vy;
        
        PhysicalCoordToScreenCoord(vx,vy,x+3.0*cos(angle),y+3.0*sin(angle));
        for (int i = 0; i<2; i++)
        {
            col.push_back(0.0f);
            col.push_back(0.0f);
            col.push_back(1.0f);
            col.push_back(0.0f);
        }
        
        glEnableVertexAttribArray(p2r.attribColorPos);
        glVertexAttribPointer(p2r.attribColorPos,4,GL_FLOAT,GL_FALSE,0,col.data());
        
        DrawLine(sx,sy,vx,vy);
        glDisableVertexAttribArray(p2r.attribColorPos);
        
    }
    
    void DrawCannonBall(double x,double y)
    {
        int sx,sy;
        PhysicalCoordToScreenCoord(sx,sy,x,y);
        
        //	    glColor3ub(255,0,0);
        std::vector<GLfloat> col;
        for (int i = 0; i < 64; i++) {
            col.push_back(1.0f);
            col.push_back(0.0f);
            col.push_back(0.0f);
            col.push_back(0.0f);
        }
        glEnableVertexAttribArray(p2r.attribColorPos);
        glVertexAttribPointer(p2r.attribColorPos,4,GL_FLOAT,GL_FALSE,0,col.data());
        
        DrawCircle(sx,sy,5,1);
        glDisableVertexAttribArray(p2r.attribColorPos);
        col.clear();
        
    }
    
    void MoveCannon(double &x,double &y,double &vx,double &vy,double m,double dt)
    {
        x+=vx*dt;
        y+=vy*dt;
        
        vy-=9.8*dt;
    }
    
    void FireCannon(
                    double &cx,double &cy,double &vx,double &vy,
                    double artX,double artY,double artAngle,double iniVel)
    {
        cx=artX;
        cy=artY;
        vx=iniVel*cos(artAngle);
        vy=iniVel*sin(artAngle);
    }
    
    void GenerateObstacle(
                          int nObstacle,int obstacleState[],double obstacleX[],double obstacleY[],double obstacleW[],double obstacleH[])
    {
        int i;
        for(i=0; i<nObstacle; i++)
        {
            obstacleState[i]=1;
            obstacleX[i]=(double)(10+rand()%70);
            obstacleY[i]=(double)(rand()%60);
            obstacleW[i]=(double)(8+rand()%8);
            obstacleH[i]=(double)(8+rand()%8);
            
            // The following if-statements forces the effective size of the
            // obstacle to be between 8x8 and 15x15.
            if(80.0<obstacleX[i]+obstacleW[i])
            {
                obstacleX[i]=80.0-obstacleW[i];
            }
            if(60.0<obstacleY[i]+obstacleH[i])
            {
                obstacleY[i]=60.0-obstacleH[i];
            }
        }
    }
    
    void DrawObstacle(
                      int nObstacle,int obstacleState[],double obstacleX[],double obstacleY[],double obstacleW[],double obstacleH[])
    {
        int i;
        for(i=0; i<nObstacle; i++)
        {
            if(obstacleState[i]!=0)
            {
                int x1,y1,x2,y2;
                PhysicalCoordToScreenCoord(x1,y1,obstacleX[i],obstacleY[i]);
                PhysicalCoordToScreenCoord(x2,y2,obstacleX[i]+obstacleW[i],obstacleY[i]+obstacleH[i]);
                
                std::vector<GLfloat> col;
                for (int i = 0; i<4; i++)
                {
                    col.push_back(0.0f);
                    col.push_back(1.0f);
                    col.push_back(0.0f);
                    col.push_back(0.0f);
                }
                glEnableVertexAttribArray(p2r.attribColorPos);
                glVertexAttribPointer(p2r.attribColorPos,4,GL_FLOAT,GL_FALSE,0,col.data());
                
                DrawRect(x1,y1,x2,y2,1);
                glDisableVertexAttribArray(p2r.attribColorPos);
                
            }
        }
    }
    
    void DrawTarget(
                    double targetX,double targetY,double targetW,double targetH)
    {
        int x1,y1,x2,y2;
        PhysicalCoordToScreenCoord(x1,y1,targetX,targetY);
        PhysicalCoordToScreenCoord(x2,y2,targetX+targetW,targetY+targetH);
        
        
        std::vector<GLfloat> col;
        for (int i = 0; i<4; i++)
        {
            col.push_back(1.0f);
            col.push_back(0.0f);
            col.push_back(0.0f);
            col.push_back(0.0f);
        }
        glEnableVertexAttribArray(p2r.attribColorPos);
        glVertexAttribPointer(p2r.attribColorPos,4,GL_FLOAT,GL_FALSE,0,col.data());
        DrawRect(x1,y1,x2,y2,1);
        glDisableVertexAttribArray(p2r.attribColorPos);
        col.clear();
        
    }
    
    void MoveTarget(double &targetX,double &targetY,const double dt)
    {
        targetY-=10*dt;
        if(0>targetY)
        {
            targetY=60.0;
        }
    }
    
    void DrawTrajectory(int nPnt,const double pnt[])
    {
        if(2<=nPnt)
        {
            glColor3ub(0,0,0);
            
            
            std::vector<GLfloat> vtx;
            std::vector<GLfloat> col;
            int i;
            for(i=0; i<nPnt; i++)
            {
                int sx,sy;
                PhysicalCoordToScreenCoord(sx,sy,pnt[i*2],pnt[i*2+1]);
                //				glVertex2i(sx,sy);
                vtx.push_back(sx);
                vtx.push_back(sy);
                
                col.push_back(0);
                col.push_back(0);
                col.push_back(0);
                col.push_back(0);
            }
            glEnableVertexAttribArray(p2r.attribVertexPos);
            glVertexAttribPointer(p2r.attribVertexPos,2,GL_FLOAT,GL_FALSE,0,vtx.data());
            glEnableVertexAttribArray(p2r.attribColorPos);
            glVertexAttribPointer(p2r.attribColorPos,4,GL_FLOAT,GL_FALSE,0,col.data());

            glDrawArrays(GL_LINE_STRIP,0,nPnt);
            glDisableVertexAttribArray(p2r.attribVertexPos);
            glDisableVertexAttribArray(p2r.attribColorPos);
            col.clear();
            
        }
    }
    
    enum {
        nObstacle=5,
        maxNumTrj=200
    };
    
    int i,key,nShot;
    double artX,artY,artAngle;
    const double PI;
    
    int nTrj;
    double trj[maxNumTrj*2];
    
    int obstacleState[nObstacle];
    double obstacleX[nObstacle],obstacleY[nObstacle];
    double obstacleW[nObstacle],obstacleH[nObstacle];
    
    int cannonState;
    double cannonX,cannonY,cannonVx,cannonVy;
    
    double targetX,targetY,targetW,targetH;
    
    
    
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

FsLazyWindowApplication::FsLazyWindowApplication() : PI(3.1415927)
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
    opt.wid=800;
    opt.hei=600;
}
/* virtual */ void FsLazyWindowApplication::Initialize(int argc,char *argv[])
{
    FsChangeToProgramDir();
    
    cannonState=0;
    nTrj=0;
    
    artX=5.0;
    artY=5.0;
    artAngle=PI/6.0;
    
    srand(time(NULL));
    
    targetX=75.0;
    targetY=60.0;
    targetW=5.0;
    targetH=5.0;
    
    nShot=0;
    
    GenerateObstacle(nObstacle,obstacleState,obstacleX,obstacleY,obstacleW,obstacleH);
    /////
    glGenTextures(1, &texIdent);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIdent);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    p2r.CompileFile("plain2d_vertexShader.glsl","plain2d_fragmentShader.glsl");
    //////
    
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
    auto key=FsInkey();
    if(FSKEY_ESC==key)
    {
        SetMustTerminate(true);
    }
    
    switch(key)
    {
        case FSKEY_UP:
            artY+=1.0;
            if(60.0<artY)
            {
                artY=60.0;
            }
            break;
        case FSKEY_DOWN:
            artY-=1.0;
            if(0.0>artY)
            {
                artY=0.0;
            }
            break;
        case FSKEY_LEFT:
            artAngle+=PI/180.0;  // 1 degree
            break;
        case FSKEY_RIGHT:
            artAngle-=PI/180.0;  // 1 degree
            break;
        case FSKEY_SPACE:
            if(cannonState==0)
            {
                cannonState=1;
                FireCannon(
                           cannonX,cannonY,cannonVx,cannonVy,
                           artX,artY,artAngle,40.0);
                nShot++;
                
                nTrj=0;
            }
            break;
    }
    
    MoveTarget(targetX,targetY,0.025);
    
    if(cannonState==1)
    {
        MoveCannon(cannonX,cannonY,cannonVx,cannonVy,1.0,0.02);
        if(cannonY<0.0 || cannonX<0.0 || 80.0<cannonX)
        {
            cannonState=0;
        }
        
        if(nTrj<maxNumTrj)
        {
            trj[nTrj*2  ]=cannonX;
            trj[nTrj*2+1]=cannonY;
            nTrj++;
        }
        
        for(i=0; i<nObstacle; i++)
        {
            if(obstacleState[i]==1 &&
               CheckHitTarget(cannonX,cannonY,obstacleX[i],obstacleY[i],obstacleW[i],obstacleH[i])==1)
            {
                printf("Hit Obstacle!\n");
                obstacleState[i]=0;
                cannonState=0;
            }
        }
        
        if(CheckHitTarget(cannonX,cannonY,targetX,targetY,targetW,targetH)==1)
        {
            printf("Hit Target!\n");
            printf("You fired %d shots.\n",nShot);
            SetMustTerminate(true);
        }
    }
    
    needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    
    DrawArtillery(artX,artY,artAngle);
    DrawObstacle(nObstacle,obstacleState,obstacleX,obstacleY,obstacleW,obstacleH);
    DrawTarget(targetX,targetY,targetW,targetH);
    
    if(cannonState==1)
    {
        DrawCannonBall(cannonX,cannonY);
        DrawTrajectory(nTrj,trj);
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

