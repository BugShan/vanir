#include <vanir/MetaData.h>
#include <vanir/Type.h>

namespace vanir
{
	MetaData::MetaData(void)
		: mTypeVec()
	{ ; }
	MetaData::~MetaData(void)
	{
		for(auto type : mTypeVec)
			delete type;
	}
};//naomespace vanir
