#include "TypeDecl.h"

namespace vanir
{
	namespace tool
	{
		std::vector<ClassDecl*>		gClassDeclVec;
		std::vector<EnumDecl*>		gEnumDeclVec;

		
		const bool HasClass(const std::string& name)
		{
			return false;
		}

		void ClearAllCache(void)
		{
			gClassDeclVec.clear();
			gEnumDeclVec.clear();
		}
	};//namespace tool
};//namespace vanir
