#include <vanir/Type.h>

namespace vanir
{
	type_id Type::suNextID = Type::INVALID_ID + 1;

	std::string SubStrName(const std::string& fullName)
	{
		const auto pos = fullName.find_last_not_of("::");
		if(pos == std::string::npos)
			return fullName;
		else
			return fullName.substr(pos, fullName.size() - pos);
	}

	Type::Type(const std::string& fullName, const unsigned int size, const unsigned int typeKind)
		: muID(suNextID++)
		, mName(SubStrName(fullName))
		, mFullName(fullName)
		, muTypeKind(typeKind)
		, muSize(size)
	{ ; }

	Type::~Type(void)
	{ ; }
};//namespace vanir
