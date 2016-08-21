#ifndef	_VANIR_PRIMITIVE_H_
#define	_VANIR_PRIMITIVE_H_

#include <vanir/Type.h>

namespace vanir
{
	class Primitive : public Type
	{
	public:
		Primitive(const std::string& fullName);
		virtual ~Primitive(void) override;
	};//class Primitive
};//namespace vanir

#endif//_VANIR_PRIMITIVE_H_
