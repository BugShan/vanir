#ifndef	_VANIR_FIELD_H_
#define	_VANIR_FIELD_H_

#include <vanir/Vanir.h>
#include <vanir/TypeTrait.h>
#include <type_traits>
#include <string>

namespace vanir
{
	class Type;
	class Field final
	{
	public:
		template<typename T>
		struct Tag
		{ ; };
	public:
		/**
		 * The constructor.
		 * @param fieldName: the name of this field
		 * @param offset:	 the offset of this field
		 */
		template<typename T>
		inline Field(const std::string& name, const unsigned int offset, Tag<T>);
		/**
		 * The destructor.
		 */
		inline ~Field(void);

	public:
		/**
		 * Get the name of this field.
		 */
		inline const std::string& GetName(void) const;
		/**
		 * Check if the field is a pointer.
		 */
		inline const bool IsPointer(void) const;
		/** 
		 * Check if the field is array.
		 */
		inline const bool IsArray(void) const;

	public:
		/**
		 * Get the type of this field
		 */
		const Type* GetFieldTypePtr(void) const;
		/**
		 * Set the value to this field of one object[ClassType].
		 * @param object: pass the object
		 * @param value:  pass the value of this field.
		 */
		void SetValue(const void* const object, const void* const value) const;
		/**
		 * Get the value from this field of one object[ClassType].
		 * @param ret:	  where the value write to
		 * @param object: pass the object
		 */
		void GetValue(void* ret, const void* const object) const;

	private:
		const std::string					mName;
		const std::string					mFieldTypeName;
		const TypeTrait						mFieldTypeTrait;

		const unsigned int					muOffset;
		const unsigned int					muSize;
	};//class Field
	
	template<typename T>
	inline Field::Field(const std::string& name, const unsigned int offset, Tag<T>)
		: mName(name)
		, mFieldTypeName(type_info<typename remove_all<T>::type>::fullName)
		, mFieldTypeTrait(TypeTrait::CreateTypeTrait<T>())
		, muOffset(offset)
		, muSize(sizeof(typename remove_all<T>::type))
	{ ; }
	inline Field::~Field(void)
	{ ; }

	inline const std::string& Field::GetName(void) const
	{
		return this->mName;
	}
	inline const bool Field::IsArray(void) const
	{
		return mFieldTypeTrait.IsPointer();
	}
	inline const bool Field::IsPointer(void) const
	{
		return mFieldTypeTrait.IsArray();
	}
};//namespace vanir
#endif//_VANIR_FIELD_H_
