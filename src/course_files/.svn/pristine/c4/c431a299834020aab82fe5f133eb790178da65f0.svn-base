#include <simplebitmap.h>

int main(int argc,char *argv[])
{
	if(2<=argc)
	{
		SimpleBitmap srcBmp;
		if(true==srcBmp.LoadPng(argv[1]))
		{
			int serial=0;
			char fn[256];
			for(int y=0; y<srcBmp.GetHeight(); y+=40)
			{
				for(int x=0; x<srcBmp.GetWidth(); x+=40)
				{
					auto cutOut=srcBmp.CutOut(x,y,40,40);
					sprintf(fn,"%d.png",serial);
					FILE *fp=fopen(fn,"wb");
					if(nullptr!=fp)
					{
						cutOut.SavePng(fp);
						serial++;
						if(200==serial)
						{
							return 0;
						}
					}
				}
			}
		}
	}
	return 0;
}
