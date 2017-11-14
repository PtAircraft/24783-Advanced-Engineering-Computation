/* ////////////////////////////////////////////////////////////

File Name: ysshellext_thicknessutil.h
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

#ifndef YSSHELLEXT_THICKNESSUTIL_IS_INCLUDED
#define YSSHELLEXT_THICKNESSUTIL_IS_INCLUDED
/* { */

#include <ysshellext.h>

class YsShellExt_ThicknessEstimation
{
public:
	class Sample
	{
	public:
		YsShell::PolygonHandle fromPlHd,toPlHd;
		YsVec3 from,to;
		YSBOOL valid;

		Sample()
		{
			valid=YSTRUE;
		}
	};

	class Preference
	{
	public:
		double opposingAngleThr;                // Unless normals are making greater angle than this threshold, won't take it as a thickness sample.
		YSBOOL excludeVertexConnectedNeighbor;  // Ignore vertex-connected polygons when shooting a ray.
		Preference();
	};

private:
	YsArray <Sample> thicknessSample;

	YsShellPolygonAttribTable <double> plgThickness;
	YsArray <YsShell::PolygonHandle> plgThicknessFilled;

public:
	YsShellExt_ThicknessEstimation();
	~YsShellExt_ThicknessEstimation();
	void CleanUp(void);
	void MakeSample(const YsShellExt &shl,const YsShellLattice &ltc,const Preference &pref,int nThread=8);
private:
	void AddSamplePerPolygon(YsArray <Sample> &sample,const YsShellExt &shl,YsShell::PolygonHandle plHd,const YsShellLattice &ltc,const Preference &pref);
	class MakeSampleThreadInfo;
	static void MakeSampleThreadCallBack(MakeSampleThreadInfo *infoPtr);

public:
	const YsArray <Sample> &GetSample(void) const;


public:
	void TrimSample(const YsShell &shl,int nThread=8);  // See research note 2015/08/13
private:
	class TrimmingLatticeThreadInfo;
	static void MakeTrimmingLatticeThreadCallBack(TrimmingLatticeThreadInfo *infoPtr);
	class TrimSampleThreadInfo;
	static void TrimSampleThreadCallBack(TrimSampleThreadInfo *infoPtr);


public:
	/*! This function will fill the polygons that do not have an assigned thickness. */
	void AssignPolygonThickness(const YsShellExt &shl);
	void SmoothPolygonThickness(const YsShellExt &shl,int nIter,int nThread=8);
private:
	void SmoothPolygonThicknessOneIteration(const YsShellExt &shl,int nThread=8);
	class SmoothPolygonThreadInfo;
	static void SmoothPolygonThreadCallBack(SmoothPolygonThreadInfo *infoPtr);

public:
	YSBOOL IsThicknessAssignedPolygon(YsShell::PolygonHandle plHd) const;
	YSBOOL IsThicknessAssignedPolygon(const YsShell &shl,YsShell::PolygonHandle plHd) const;
	double GetPolygonThickness(YsShell::PolygonHandle plHd) const;
	double GetPolygonThickness(const YsShell &shl,YsShell::PolygonHandle plHd) const;
};


/* } */
#endif
