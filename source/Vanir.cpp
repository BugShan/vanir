#include <vanir/Vanir.h>
#include <vanir/Class.h>
#include <map>

namespace vanir
{
	std::vector<Type*> gTypeVec;

	const Type* const GetTypeByID(const type_id id)
	{
		for(auto typePtr : gTypeVec)
		{
			if(typePtr->GetID() == id)
				return typePtr;
		}
		return nullptr;
	}

	const Type* const GetTypeByName(const std::string& name)
	{
		for(auto typePtr : gTypeVec)
		{
			if(typePtr->GetName() == name)
				return typePtr;
		}
		return nullptr;
	}

	const std::vector<Type*>& GetAllTypeList(void)
	{
		return gTypeVec;
	}
};//namespace vanir
