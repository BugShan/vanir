#ifndef	_VANIR_FIELD_H_
#define	_VANIR_FIELD_H_

#include <vanir/Vanir.h>
#include <vanir/TypeTrait.h>
#include <type_traits>
#include <string>

namespace vanir
{
	namespace detail
	{
		template<typename T>
		struct field_trait;//struct field_trait
		template<typename Class, typename T>
		struct field_trait<T(Class::*)>
		{
			using field_type = T;
			using class_type = Class;
		};//struct field_Trait<T(Class::*)>
	};//namespace detail

	class Type;
	class Field final
	{
	public:
		/**
		 * The constructor.
		 * @param fieldName:	the name of this field
		 * @param fieldAddress:	the pointer to this field
		 */
		template<typename T, typename ClassType = typename detail::field_trait<T>::class_type, typename FieldType = typename detail::field_trait<T>::field_type>
		inline Field(const std::string& name, const T fieldAddress);
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
	
	template<typename T, typename ClassType, typename FieldType>
	inline Field::Field(const std::string& name, const T fieldAddress)
		: mName(name)
		, mFieldTypeName(type_info<FieldType>::fullname)
		, mFieldTypeTrait(TypeTrait::CreateTypeTrait<FieldType>())
		, muOffset((size_t)(&((ClassType*)0->*fieldAddress)))
		, muSize(sizeof(FieldType))
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
