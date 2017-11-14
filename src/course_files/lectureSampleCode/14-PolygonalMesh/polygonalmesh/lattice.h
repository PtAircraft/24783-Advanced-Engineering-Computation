#ifndef LATTICE_IS_INCLUDED
#define LATTICE_IS_INCLUDED
/* { */

template <class T>
class Lattice3d
{
protected:
    int nx,ny,nz;
    std::vector <T> elem;
    YsVec3 min,max;
public:
	Lattice3d()
	{
		nx=0;
		ny=0;
		nz=0;
		min=YsVec3::Origin();
		max=YsVec3::Origin();
	}

    /*! Create a lattice with nx*ny*nz blocks.  To store nodal information, the length of the
        storage actually allocated will be (nx+1)*(ny+1)*(nz+1).  */
    void Create(int nx,int ny,int nz,const YsVec3 &min,const YsVec3 &max)
    {
		if(nx<1)
		{
			nx=1;
		}
		if(ny<1)
		{
			ny=1;
		}
		if(nz<1)
		{
			nz=1;
		}
		elem.clear();
		elem.resize((nx+1)*(ny+1)*(nz+1));
		this->nx=nx;
		this->ny=ny;
		this->nz=nz;
		this->min=min;
		this->max=max;
	}


    /*! Returns number of blocks in X,Y, and Z direction. */
    YSSIZE_T Nx(void) const
    {
		return nx;
	}
    YSSIZE_T Ny(void) const
    {
		return ny;
	}
    YSSIZE_T Nz(void) const
    {
		return nz;
	}
    /*! Returns the dimension of one block. */
    YsVec3 GetBlockDimension(void) const
    {
		YsVec3 d=max-min;
		d.DivX((double)nx);
		d.DivY((double)ny);
		d.DivZ((double)nz);
		return d;
	}
    /*! Returns the minimum (x,y,z) of the block at (bx,by,bz). */
    YsVec3 GetBlockPosition(int ix,int iy,int iz) const
    {
		auto d=GetBlockDimension();
		d.MulX((double)ix);
		d.MulY((double)iy);
		d.MulZ((double)iz);
		return min+d;
	}
    /*! Returns the index of the block that encloses the given position. */
    YsVec3i GetBlockIndex(const YsVec3 &pos) const
    {
		auto d=pos-min;
		auto boxD=GetBlockDimension();

		int ix=(int)(d.x()/boxD.x());
		int iy=(int)(d.y()/boxD.y());
		int iz=(int)(d.z()/boxD.z());
		return YsVec3i(ix,iy,iz);
	}

    /*! Returns if the block index is within the valid range.
        The lattice elements can be nodal value or cell value.  To support the nodal values,
        this class allocates (nx+1)*(ny+1)*(nz+1) elems.  Therefore, the index is valid
        and this function returns true, if:
           0<=idx.x() && idx.x()<=nx && 0<=idx.y() && idx.y()<=ny && 0<=idx.z() && idx.z()<=nz. */
    bool IsInRange(const YsVec3i idx) const
    {
		return (0<=idx.x() && idx.x()<=nx && 
		        0<=idx.y() && idx.y()<=ny && 
		        0<=idx.z() && idx.z()<=nz);
	}

    /*! Returns a reference to the lattice element at the index. */
    T &operator[](const YsVec3i idx)
    {
		return elem[idx.z()*(nx+1)*(ny+1)+idx.y()*(nx+1)+idx.x()];
	}
    const T &operator[](const YsVec3i idx) const
    {
		return elem[idx.z()*(nx+1)*(ny+1)+idx.y()*(nx+1)+idx.x()];
	}
};

/* } */
#endif
