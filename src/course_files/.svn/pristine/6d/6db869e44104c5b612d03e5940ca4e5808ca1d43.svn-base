#include <fslazywindow.h>

#include <simplebitmap.h>
#include <hashtable.h>


template <>
unsigned long long int HashBase<SimpleBitmap>::HashCode(const SimpleBitmap &key) const
{
	auto rgba=key.GetBitmapPointer();
	const unsigned int coeff[5]=
	{
		2,3,5,7,11
	};
	unsigned long long int code=0;
	for(int i=0; i<key.GetTotalNumComponent(); ++i)
	{
		code+=coeff[i%5]*(unsigned int)rgba[i];
	}
	return code;
}



class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	bool needRedraw;

	SimpleBitmap sourceBmp;
	HashTable <SimpleBitmap,int> bmpToId;

	// >> for bonus problem
	int mode; // 0:showing found blocks    1:Showing pure map
	SimpleBitmapTemplate <int,1> codedMap;
	int sx,sy;
	std::vector <SimpleBitmap> blockCodeToBmp;

	std::vector <SimpleBitmap> backgroundBlockBmp;
	bool BitmapConsistsOfBlueAndYellowOnly(const SimpleBitmap &bmp) const;
	int CompareBlueAndYellow(const SimpleBitmap &bmp1,const SimpleBitmap &bmp2) const;
	// << for bonus

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


bool FsLazyWindowApplication::BitmapConsistsOfBlueAndYellowOnly(const SimpleBitmap &bmp) const
{
	auto rgba=bmp.GetBitmapPointer();
	auto numPix=bmp.GetWidth()*bmp.GetHeight();
	for(int i=0; i<numPix; ++i)
	{
		if((rgba[i*4]==255 && rgba[i*4+1]==255 && rgba[i*4+2]==0) || // Yellow=R+G
		   (rgba[i*4]==0   && rgba[i*4+1]==0   && rgba[i*4+2]==255)) // Blue
		{
			continue;
		}
		return false;
	}
	return true;
}
int FsLazyWindowApplication::CompareBlueAndYellow(const SimpleBitmap &bmp1,const SimpleBitmap &bmp2) const
{
	if(40!=bmp1.GetWidth() || 40!=bmp1.GetHeight() ||
	   40!=bmp2.GetWidth() || 40!=bmp2.GetWidth())
	{
		return 10000;
	}

	int nErr=0;
	auto rgba1=bmp1.GetBitmapPointer();
	auto rgba2=bmp2.GetBitmapPointer();
	auto numPix=bmp1.GetWidth()*bmp1.GetHeight();
	for(int i=0; i<numPix; ++i)
	{
		if(((rgba1[i*4]==255 && rgba1[i*4+1]==255 && rgba1[i*4+2]==0) ||     // Yellow=R+G
		    (rgba1[i*4]==0   && rgba1[i*4+1]==0   && rgba1[i*4+2]==255)) &&  // Blue
		   ((rgba2[i*4]==255 && rgba2[i*4+1]==255 && rgba2[i*4+2]==0) ||     // Yellow=R+G
		    (rgba2[i*4]==0   && rgba2[i*4+1]==0   && rgba2[i*4+2]==255)))
		{
			if(rgba1[i*4  ]!=rgba2[i*4  ] ||
			   rgba1[i*4+1]!=rgba2[i*4+1] ||
			   rgba1[i*4+2]!=rgba2[i*4+2])
			{
				++nErr;
			}
		}
	}
	return nErr;
}


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
	sx=0;
	sy=0;
	mode=0;

	if(2<=argc)
	{
		FILE *fp=fopen(argv[1],"rb");
		if(sourceBmp.LoadPng(fp))
		{
			printf("Loaded %dx%d\n",sourceBmp.GetWidth(),sourceBmp.GetHeight());

			int assignId=0;
			int numBlock=0;
			for(int y=0; y<sourceBmp.GetHeight(); y+=40)
			{
				for(int x=0; x<sourceBmp.GetWidth(); x+=40)
				{
					auto block=sourceBmp.CutOut(x,y,40,40);
					auto idPtr=bmpToId[block];
					if(nullptr==idPtr)
					{
						bmpToId.Update(block,assignId);
						// >> Bonus
						blockCodeToBmp.push_back(block);

						if(BitmapConsistsOfBlueAndYellowOnly(block))
						{
							backgroundBlockBmp.push_back(block);
						}
						// << Bonus
						++assignId;
					}
					++numBlock;
				}
			}
			printf("Found %d block types in %d total blocks.\n",assignId,numBlock);
		}
		fclose(fp);
	}
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		SetMustTerminate(true);
	}

	// Bonus >>
	if(FSKEY_SPACE==key && 0==mode)
	{
		codedMap.Create(sourceBmp.GetWidth()/40,sourceBmp.GetHeight()/40);
		for(int y=0; y<codedMap.GetHeight(); ++y)
		{
			for(int x=0; x<codedMap.GetWidth(); ++x)
			{
				auto block=sourceBmp.CutOut(x*40,y*40,40,40);
				auto idPtr=bmpToId[block];
				if(nullptr!=idPtr)
				{
					(*codedMap.GetEditablePixelPointer(x,y))=*idPtr;
				}
				else
				{
					(*codedMap.GetEditablePixelPointer(x,y))=-1;
				}
			}
		}
		mode=1;
	}
	else if(FSKEY_SPACE==key && 1==mode)
	{
		codedMap.Create(sourceBmp.GetWidth()/40,sourceBmp.GetHeight()/40);
		for(int y=0; y<codedMap.GetHeight(); ++y)
		{
			for(int x=0; x<codedMap.GetWidth(); ++x)
			{
				auto block=sourceBmp.CutOut(x*40,y*40,40,40);
				std::vector <const SimpleBitmap *> matchBmp;
				if(!BitmapConsistsOfBlueAndYellowOnly(block))
				{
					for(auto &bgBmp : backgroundBlockBmp)
					{
						if(0==CompareBlueAndYellow(bgBmp,block))
						{
							matchBmp.push_back(&bgBmp);
						}
					}
					if(1==matchBmp.size())
					{
						block=*matchBmp[0];
					}
					else if(0==matchBmp.size())
					{
						printf("No match.\n");
					}
					else
					{
						printf("More than one match (%d). Take one of them.\n",(int)matchBmp.size());
						block=*matchBmp[0];
					}
				}

				auto idPtr=bmpToId[block];
				if(nullptr!=idPtr)
				{
					(*codedMap.GetEditablePixelPointer(x,y))=*idPtr;
				}
				else
				{
					(*codedMap.GetEditablePixelPointer(x,y))=-1;
				}
			}
		}
		mode=1;
	}

	if(FSKEY_LEFT==key && 1==mode)
	{
		sx++;
	}
	if(FSKEY_RIGHT==key && 1==mode)
	{
		sx--;
	}
	if(FSKEY_UP==key && 1==mode)
	{
		sy++;
	}
	if(FSKEY_DOWN==key && 1==mode)
	{
		sy--;
	}
	// Bonus <<

	needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
	needRedraw=false;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if(0==mode)
	{
		int x=0,y=40;
		for(auto handle=bmpToId.First(); bmpToId.IsNotNull(handle); handle=bmpToId.Next(handle))
		{
			auto key=bmpToId.GetKey(handle);
			key.Invert();
			glRasterPos2i(x,y);
			glDrawPixels(40,40,GL_RGBA,GL_UNSIGNED_BYTE,key.GetBitmapPointer());
			x+=40;
			if(1200<=x)
			{
				y+=40;
				x=0;
			}
		}
	}
	// Bonus >>
	else if(1==mode)
	{
		for(int y=0; y*40<800; ++y)
		{
			for(int x=0; x*40<1200; ++x)
			{
				if(codedMap.IsInRange(x+sx,y+sy))
				{
					auto code=*codedMap.GetPixelPointer(x+sx,y+sy);
					if(0<=code && code<blockCodeToBmp.size())
					{
						auto bmp=blockCodeToBmp[code];
						bmp.Invert();
						glRasterPos2i(x*40,y*40+40);
						glDrawPixels(40,40,GL_RGBA,GL_UNSIGNED_BYTE,bmp.GetBitmapPointer());
					}
				}
			}
		}
	}
	// Bonus <<
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
