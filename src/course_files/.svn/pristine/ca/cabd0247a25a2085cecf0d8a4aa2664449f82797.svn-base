#include "polygonalmesh.h"


bool PolygonalMesh::IsASCIIStl(const char fn[])
{
	FILE *fp=fopen(fn,"rb");
	if(nullptr!=fp)
	{
		char buf[1024];
		int nBuf=fread(buf,1,1024,fp);
		fclose(fp);

		bool solid=false,facet=false,vertex=false,loop=false;
		for(int i=0; i<nBuf-6; ++i)
		{
			if(0==strncmp(buf+i,"solid",5))
			{
				solid=true;
			}
			if(80<=i)
			{
				if(0==strncmp(buf+i,"facet",5))
				{
					facet=true;
				}
				else if(0==strncmp(buf+i,"vertex",6))
				{
					vertex=true;
				}
				else if(0==strncmp(buf+i,"loop",4))
				{
					loop=true;
				}
			}
		}

		return (solid && facet && vertex && loop);
	}
	return false;
}



bool PolygonalMesh::IsLittleEndian(void)
{
	int i=1;
	char *ptr=(char *)&i;
	return (1==*ptr);
}

unsigned int PolygonalMesh::BinaryToInt(const unsigned char dat[4])
{
	if(true==IsLittleEndian())
	{
		unsigned char b0=dat[0];
	    unsigned char b1=dat[1];
	    unsigned char b2=dat[2];
	    unsigned char b3=dat[3];
	    return b0+b1*0x100+b2*0x10000+b3*0x1000000;
	}
	else
	{
		unsigned char b0=dat[3];
	    unsigned char b1=dat[2];
	    unsigned char b2=dat[1];
	    unsigned char b3=dat[0];
	    return b0+b1*0x100+b2*0x10000+b3*0x1000000;
	}
}
float PolygonalMesh::BinaryToFloat(const unsigned char dat[4])
{
	if(true==IsLittleEndian())
	{
	    const float *fPtr=(const float *)dat;
	    return *fPtr;
	}
	else
	{
		const unsigned char flipped[4]=
		{
			dat[3],dat[2],dat[1],dat[0]
		};
	    const float *fPtr=(const float *)flipped;
	    return *fPtr;
	}
}

bool PolygonalMesh::LoadBinStl(const char fn[])
{
	if(true==IsASCIIStl(fn))
	{
		printf("Is ASCII format\n");
		return false;
	}



	FILE *fp=fopen(fn,"rb");
	if(nullptr!=fp)
	{
		unsigned char buf[256];

		if(80!=fread(buf,1,80,fp))
		{
			fclose(fp);
			return false;
		}

		fread(buf,1,4,fp);
		auto nTri=BinaryToInt(buf);
		printf("%d triangles expected\n",nTri);

		while(50==fread(buf,1,50,fp))
		{
			auto nx=BinaryToFloat(buf);
			auto ny=BinaryToFloat(buf+4);
			auto nz=BinaryToFloat(buf+8);

			float xyz[9]=
			{
				BinaryToFloat(buf+12),
				BinaryToFloat(buf+16),
				BinaryToFloat(buf+20),
				BinaryToFloat(buf+24),
				BinaryToFloat(buf+28),
				BinaryToFloat(buf+32),
				BinaryToFloat(buf+36),
				BinaryToFloat(buf+40),
				BinaryToFloat(buf+44),
			};

			VertexHandle triVtHd[3]=
			{
				NullVertex(),
				NullVertex(),
				NullVertex(),
			};

			for(int i=0; i<3; ++i)
			{
				const YsVec3 newVtPos(xyz[i*3],xyz[i*3+1],xyz[i*3+2]);
				triVtHd[i]=AddVertex(newVtPos);
			}

			auto plHd=AddPolygon(3,triVtHd);
			SetPolygonNormal(plHd,YsVec3(nx,ny,nz));
			SetPolygonColor(plHd,YsBlue());
		}

		fclose(fp);
		return true;
	}
	return false;
}

