#include <vanir/Field.h>
#include <vanir/Type.h>

namespace vanir
{
	const Type* Field::GetFieldTypePtr(void) const
	{
		if(!mFieldTypeName.empty())
			return GetTypeByName(mFieldTypeName);
		return nullptr;
	}
	void Field::SetValue(const void* const object, const void* const value) const
	{
		void* address = static_cast<unsigned char*>(const_cast<void*>(object)) + muOffset;
		memcpy(address, value, muSize);
	}
	void Field::GetValue(void* ret, const void* const object) const
	{
		void* address = static_cast<unsigned char*>(const_cast<void*>(object)) + muOffset;
		memcpy(ret, address, muSize);
	}
};//namespace vanir
