#include <vanir/Vanir.h>
#include <vanir/Primitive.h>
#include <vanir/VanirInternal.h>
#include <map>

namespace vanir
{
	std::vector<const Type*>		gTypeVec;
	std::map<std::string, const Type*>	gTypeMap;

	void InitVanir(void)
	{
		RegisterType<bool>();
		RegisterType<char>();
		RegisterType<unsigned char>();
		RegisterType<short>();
		RegisterType<unsigned short>();
		RegisterType<int>();
		RegisterType<unsigned int>();
		RegisterType<long>();
		RegisterType<unsigned long>();
		RegisterType<long long>();
		RegisterType<unsigned long long>();
		RegisterType<float>();
		RegisterType<double>();
	}
	void LoadModule(Module& module)
	{
		module.Init();
	}

	const Type* const GetTypeByID(const type_id id)
	{
		for(const auto typePtr : gTypeVec)
		{
			if(typePtr->GetID() == id)
				return typePtr;
		}
		return nullptr;
	}

	const Type* const GetTypeByName(const std::string& name)
	{
		auto find_it = gTypeMap.find(name);
		if(find_it != gTypeMap.end())
			return find_it->second;
		else
			return nullptr;
	}

	const std::vector<const Type*>& GetAllTypeList(void)
	{
		return gTypeVec;
	}

	void RegisterType(const Type* const typePtr)
	{
		auto find_it = gTypeMap.find(typePtr->GetFullName());
		if(find_it == gTypeMap.end())
		{
			gTypeVec.push_back(typePtr);
//			gTypeMap[typePtr->GetFullName()] = typePtr;
			gTypeMap.insert(std::pair<std::string, const Type*>(typePtr->GetFullName(), typePtr));
		}
	}
};//namespace vanir
