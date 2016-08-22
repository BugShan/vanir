#ifndef	_VANIR_PRIMITIVE_H_
#define	_VANIR_PRIMITIVE_H_

#include <vanir/Type.h>

namespace vanir
{
	class Primitive : public Type
	{
		template<typename T>
		friend const Type* const RegisterType(void);
		template<typename T>
		friend Type* CreateType(void);
	private:
		Primitive(const std::string& fullName, const unsigned int size);
		virtual ~Primitive(void) override;
	};//class Primitive
};//namespace vanir

#endif//_VANIR_PRIMITIVE_H_
