#ifndef YSPROPERTYFILE_IS_INCLUDED
#define YSPROPERTYFILE_IS_INCLUDED

#include <memory>

#include "ysdef.h"
#include "ysstring.h"
#include "ysavltree.h"

class YsPropertyFileIO
{
public:
	class Property
	{
	friend class YsPropertyFileIO;
	private:
		YsString tag;
		virtual YsString FormatString(void) const=0;
		virtual YSRESULT Recognize(const YsConstArrayMask <YsString> &argv)=0;
	};

	class PropertyYSBOOL : public Property
	{
	friend class YsPropertyFileIO;
	private:
		YSBOOL *varPtr;
		virtual YsString FormatString(void) const;
		virtual YSRESULT Recognize(const YsConstArrayMask <YsString> &argv);
	};

private:
	YsArray <std::shared_ptr <Property> > prop;
	YsAVLTree <YsString,std::shared_ptr <Property> > tagToPropPtr;
	YsString errStr;

public:
	/*! Add a property.  The pointer to propRef will be retained in this class object.
	*/
	void AddProperty(YSBOOL &propRef,const YsString &tag);


	/*! Save to a text-output stream.
	*/
	void Save(class YsTextOutputStream &outStream);

	/*! Read from a text-output stream.
	*/
	YSRESULT Load(class YsTextInputStream &inStream);
};

#endif
