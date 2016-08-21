#include <vanir/Primitive.h>
#include <vanir/Vanir.h>
#include <vanir/Class.h>
#include <map>

namespace vanir
{
	std::vector<const Type*>		gTypeVec;
	std::map<std::string, const Type*>	gTypeMap;

	void InitVanir(void)
	{
		RegisterType(new Primitive("bool"));
		RegisterType(new Primitive("char"));
		RegisterType(new Primitive("unsigned char"));
		RegisterType(new Primitive("short"));
		RegisterType(new Primitive("unsigned short"));
		RegisterType(new Primitive("int"));
		RegisterType(new Primitive("unsigned int"));
		RegisterType(new Primitive("long"));
		RegisterType(new Primitive("unsigned long"));
		RegisterType(new Primitive("long long"));
		RegisterType(new Primitive("unsigned long long"));
		RegisterType(new Primitive("float"));
		RegisterType(new Primitive("double"));
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
