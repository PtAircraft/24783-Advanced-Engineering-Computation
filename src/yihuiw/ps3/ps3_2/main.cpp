#include <fslazywindow.h>
#include "simplebitmap.h"
#include "hashtable.h"


template <>
typename HashCommon::CodeType HashBase<SimpleBitmap>::HashCode(const SimpleBitmap &key) const
{
    HashCommon::CodeType sum = 0;
    int num = key.GetTotalNumComponent();
    auto p = key.GetBitmapPointer();
    int k = 0;
    for (int i = 0; i < num; i++)
    {
        if(k == 0)
        {
            sum = sum + 2 * p[i];
        }
        if(k == 1)
        {
            sum = sum + 3 * p[i];
        }
        if(k == 2)
        {
            sum = sum + 5 * p[i];
        }
        if(k == 3)
        {
            sum = sum + 7 * p[i];
        }
        if(k == 4)
        {
            sum = sum + 11 * p[i];
        }
        k++;
        if (k == 5)
        {
            k = 0;
        }
    }
    return sum;
}
class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	bool needRedraw;
    SimpleBitmap bmp;   //input png.
    SimpleBitmap cut;   //cut png.
    SimpleBitmap show;  //whole pic png.
    int x, y;
    int wid, hei;
    HashTable<SimpleBitmap, int> ht;
    int hc;  // hashcode.
    int ID;  //ID number
    int state;
    int xs, ys; //the starting point of showing whole picture
    
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
    if (argc < 2) {
        printf("Usage: testbitmap <png-file>\n");
    }else if (false == bmp.LoadPng(argv[1])) {
        printf("Falied to read a ,PNG file.");
    }
    
    //get the wid and hei for input png.
//    nx = bmp.GetWidth();
//    ny = bmp.GetHeight();
    
    //x and y for plot.
    x = 0;
    y = 0;
    
    //wid and hei for each cut.
    wid = hei = 40;
    
    ID = 0;
    
    while(true) {
      //  printf("test1\n");
        cut = bmp.CutOut(x, y, wid, hei);
      //  printf("test2\n");
        if (!ht.IsIncluded(cut)) {
            ht.Update(cut, ID);
            ID++;
        }
       // printf("test3\n");
        x = x + 40;
       // printf("x: %d\n",x);
       // printf("y: %d\n",y);

        if (!bmp.IsXInRange(x)) {
            
            x = 0;
            y = y + 40;
        }
       // printf("test4\n");
        if (!bmp.IsInRange(x,y)) {
            break;
        }
    }
    state = 0;
    xs = 0;
    ys = 0;
    
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		SetMustTerminate(true);
	}
    if(FSKEY_SPACE == key) {
        state += 1;
        
        if (state > 1) {
            state = 0;
        }
    }
    if (state == 1) {
        show = bmp.CutOut(xs,ys,1200,800);
        if (FSKEY_LEFT == key) {
            xs = xs - 40;
        }
        if (xs < 0)
        {
            xs = 0;
        }
        if (FSKEY_RIGHT == key) {
            xs = xs + 40;
        }
        if (xs > (bmp.GetWidth() - 1200)) {
            xs = (bmp.GetWidth() - 1200);
        }
        if (FSKEY_DOWN == key) {
            ys = ys + 40;
        }
        if (ys >= (bmp.GetHeight() - 800))
        {
            ys = (bmp.GetHeight() - 800);
            
        }
        if (FSKEY_UP == key) {
            ys = ys - 40;
        }
        if (ys < 0) {
            ys = 0;
        }
    }


	needRedraw=true;
   
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3ub(0, 0, 255);
    if (state == 0) {
        int row = 0;
        int col = 0;
        for(auto hd=ht.First(); true==ht.IsNotNull(hd); hd=ht.Next(hd))
        {
            SimpleBitmap bmp = ht.GetKey(hd);
            glRasterPos2i(col * wid,(row + 1) * hei);
            bmp.Invert();
            glDrawPixels(bmp.GetWidth(),bmp.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,bmp.GetBitmapPointer());
            col++;
            if(col >= 30) {
                col = 0;
                row++;
            }
        }
    }
    if (state == 1)
    {
        glRasterPos2i(0,800 - 1);
        show.Invert();
        glDrawPixels(show.GetWidth(),show.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,show.GetBitmapPointer());
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
