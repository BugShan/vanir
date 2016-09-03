#ifndef	_VANIR_TYPE_H_
#define	_VANIR_TYPE_H_

#include <vanir/Vanir.h>
#include <string>

namespace vanir
{
	class Type
	{
		template<typename T>
		friend const Type* const RegisterType(void);
		template<typename T>
		friend Type* CreateType(void);
	public:
		/**
		 * Get the id of this Type.
		 */
		inline const type_id GetID(void)		const;
		/**
		 * Get the name of this Type.
		 */
		inline const std::string& GetName(void)		const;
		/**
		 * Get the fully qualified name of this Type.
		 */
		inline const std::string& GetFullName(void)	const;
		/**
		 * Get the size of this Type.
		 */
		inline const unsigned int GetSize(void) const;
		/**
		 * Determine if the Type is a Class or Struct.
		 */
		inline const bool IsClass(void) const;
		/**
		 * Determine if the Type is a Enum.
		 */
		inline const bool IsEnum(void) const;
		/**
		 * Determine if the Type is a Array.
		 */
		inline const bool IsArray(void) const;
		/**
		 * Determine if the Type is a Primitive type[char, int, float, etc].
		 */
		inline const bool IsPrimitive(void) const;

	public:
		/**
		 * Determine if the type of current is same as the specified.
		 */
		inline const bool operator =(const Type&) const;

	public:
		enum { INVALID_ID = 0 };

	protected:
		Type(const std::string& fullName, const unsigned int size, const unsigned int typeKind);
		/**
		 * The destructor.
		 */
		virtual ~Type(void);
	protected:
		enum
		{
			TYPE_KIND_CLASS		= 1 << 0,
			TYPE_KIND_ENUM		= 1 << 1,
			TYPE_KIND_ARRAY		= 1 << 2,
			TYPE_KIND_PRIMITIVE	= 1 << 3,
		};
	private:
		const type_id						muID;
		const std::string					mName;
		const std::string					mFullName;
		const unsigned int					muTypeKind;
		const unsigned int					muSize;

		static type_id						suNextID;
	};//class Type
	inline const type_id Type::GetID(void) const
	{ return this->muID; }
	inline const std::string& Type::GetName(void) const
	{ return this->mName; }
	inline const std::string& Type::GetFullName(void) const
	{ return this->mFullName; }

	inline const bool Type::operator = (const Type& other) const
	{ return this->muID == other.muID; }

	inline const bool Type::IsClass(void) const
	{ return this->muTypeKind & TYPE_KIND_CLASS; }
	inline const bool Type::IsEnum(void) const
	{ return this->muTypeKind & TYPE_KIND_ENUM; }
	inline const bool Type::IsArray(void) const
	{ return this->muTypeKind & TYPE_KIND_ARRAY; }
	inline const bool Type::IsPrimitive(void) const
	{ return this->muTypeKind & TYPE_KIND_PRIMITIVE; }
};//namespace vanir
#endif//_VANIR_TYPE_H_
