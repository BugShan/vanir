#include <vanir/Field.h>
#include <vanir/Type.h>

namespace vanir
{
	const Type* Field::GetFieldTypePtr(void) const
	{
		if(mFieldTypeID != Type::INVALID_ID)
			return GetTypeByID(mFieldTypeID);
		return nullptr;
	}
	void Field::SetValue(const void* const object, const void* const value)
	{
		void* address = static_cast<unsigned char*>(const_cast<void*>(object)) + muOffset;
		memcpy(address, value, muSize);
	}
	void Field::GetValue(void* ret, const void* const object)
	{
		void* address = static_cast<unsigned char*>(const_cast<void*>(object)) + muOffset;
		memcpy(ret, address, muSize);
	}
};//namespace vanir
