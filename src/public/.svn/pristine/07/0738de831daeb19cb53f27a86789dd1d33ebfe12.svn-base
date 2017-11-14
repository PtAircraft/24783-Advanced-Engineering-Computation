#include "yspropertyfile.h"
#include "ystextstream.h"

void YsPropertyFileIO::AddProperty(YSBOOL &propRef,const YsString &tag)
{
	auto *propPtr=new PropertyYSBOOL;
	propPtr->varPtr=&propRef;
	propPtr->tag=tag;

	this->prop.Increment();
	this->prop.back().reset(propPtr);
	tagToPropPtr.Insert(tag,this->prop.back());
}



/* virtual */ YsString YsPropertyFileIO::PropertyYSBOOL::FormatString(void) const
{
	YsString str;
	str=tag;
	str.Append(" ");
	str.Append(YsBoolToStr(*varPtr));
	return str;
}
/* virtual */ YSRESULT YsPropertyFileIO::PropertyYSBOOL::Recognize(const YsConstArrayMask <YsString> &argv)
{
	if(0==argv[0].Strcmp(tag) && 2==argv.size())
	{
		*varPtr=YsStrToBool(argv[1]);
		return YSOK;
	}
	return YSERR;
}


void YsPropertyFileIO::Save(YsTextOutputStream &outStream)
{
	for(auto &p : prop)
	{
		auto str=p->FormatString();
		outStream.Printf("%s\n",str.data());
	}
}
YSRESULT YsPropertyFileIO::Load(YsTextInputStream &inStream)
{
	YSRESULT res=YSOK;
	errStr.clear();

	while(YSTRUE!=inStream.EndOfFile())
	{
		auto str=inStream.Fgets();
		auto argv=str.Argv();
		if(0<=argv.size())
		{
			auto treeNdHd=tagToPropPtr.FindNode(argv[0]);
			if(treeNdHd!=nullptr)
			{
				auto propPtr=tagToPropPtr.GetValue(treeNdHd);
				if(YSOK!=propPtr->Recognize(argv))
				{
					YsString err;
					err="Cannot recognize:";
					err.Append(str);
					fprintf(stderr,"%s\n",err.data());
					res=YSERR;
				}
			}
		}
	}
	return res;
}
