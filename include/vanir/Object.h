#ifndef	_VANIR_OBJECT_H_
#define	_VANIR_OBJECT_H_

#include <vanir/Vanir.h>

namespace vanir
{
	class Type;
	class RUNTIME Object
	{
	public:
		Object(void) { ; }
		virtual ~Object(void) { ; }

	public:
		virtual Type* GetType(void) const = 0;
	};//class Object
};//namespace vanir

#endif//_VANIR_OBJECT_H_
