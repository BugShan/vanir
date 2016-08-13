#include <vanir/Type.h>

namespace vanir
{
	type_id Type::suNextID = Type::INVALID_ID + 1;

	Type::Type(const std::string& fullName, const unsigned int typeKind)
		: muID(suNextID++)
		, mName()
		, mFullName(fullName)
		, muTypeKind(typeKind)
	{
		auto pos = mName.find_last_of("::");
		mName = mFullName.substr(pos, mFullName.size() - pos);
	}

	Type::~Type(void)
	{ ; }
};//namespace vanir
