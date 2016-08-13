#include <vanir/Class.h>
#include <vanir/Vanir.h>
#include <vanir/Field.h>
#include <vanir/Method.h>


namespace vanir
{
	Class::Class(const std::string& fullName)
		: Type(fullName, Type::TYPE_KIND_CLASS)
		, mBaseTypeNameVec()
		, mMethodPtrVec()
		, mFieldPtrVec()
	{ ; }

	Class::~Class(void)
	{
		for(auto methodPtr : mMethodPtrVec)
			delete methodPtr;
		for(auto fieldPtr : mFieldPtrVec)
			delete fieldPtr;
	}

	const Field* const Class::GetFieldPtr(const std::string& fieldName) const
	{
		for(auto fieldPtr : mFieldPtrVec)
		{
			if(fieldName == fieldPtr->GetName())
				return fieldPtr;
		}
		return nullptr;
	}
	const Method* const Class::GetMethodPtr(const std::string& methodName) const
	{
		for(auto methodPtr : mMethodPtrVec)
		{
			if(methodName == methodPtr->GetName())
				return methodPtr;
		}
		return nullptr;
	}

	const std::vector<const Class* const> Class::GetAllBaseTypeVec(void) const
	{
		std::vector<const Class* const> ret;
		for(auto& name : mBaseTypeNameVec)
		{
			const Type* const type = vanir::GetTypeByName(name);
			if(type)
				ret.push_back(static_cast<const Class* const>(type));
		}
		return ret;
	}
};//namespace vanir
