#ifndef	_VANIR_TYPETRAIT_H_
#define	_VANIR_TYPETRAIT_H_

namespace vanir
{
	class TypeTrait final
	{
	public:
		enum
		{
			ARRAY		= 1 << 0,
			LEFT_REF	= 1 << 1,
			RIGHT_REF	= 1 << 2,
			POINTER		= 1 << 4,

			REFERENCE	= LEFT_REF | RIGHT_REF,

			ON_STACK	= 0x0F,
			ON_DEAP		= 0xF0,
		};
	public:
		template<typename T>
		static const TypeTrait CreateTypeTrait(void);

	public:
		inline const bool IsArray(void) const;
		inline const bool IsReference(void) const;
		inline const bool IsPointer(void) const;

	private:
		unsigned char	value;
	};//class TypeTrait

	template<typename T>
	const TypeTrait TypeTrait::CreateTypeTrait(void)
	{
		unsigned char value = 0x00;
		if(std::is_array<T>::value)
			value |= TypeTrait::ARRAY;
		else if(std::is_reference<T>::value)
			value |= TypeTrait::LEFT_REF;
		else if(std::is_rvalue_reference<T>::value)
			value |= TypeTrait::RIGHT_REF;
		else if(std::is_pointer<T>::value)
			value |= TypeTrait::POINTER;
		TypeTrait ret;
		ret.value = value;
		return ret;
	}
	inline const bool TypeTrait::IsArray(void) const
	{
		return value | TypeTrait::ARRAY;
	}
	inline const bool TypeTrait::IsPointer(void) const
	{
		return value | TypeTrait::POINTER;
	}
	inline const bool TypeTrait::IsReference(void) const
	{
		return value | TypeTrait::REFERENCE;
	}
};//namespace vanir

#endif//_VANIR_TYPETRAIT_H_
