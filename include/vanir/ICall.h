#ifndef	_VANIR_ICALL_H_
#define	_VANIR_ICALL_H_

#include <initializer_list>

namespace vanir
{
	class ICall
	{
	public:
		virtual ~ICall(void);
	public:
		/**
		 * Get the count of this method's parameter.
		 */
		virtual const unsigned int GetParameterCount(void) const = 0;
	public:
		/**
		 * Call this method.
		 * @param ret:		write the return of this method into ret.
		 * @param object:	the pointer to the object which owns this method.
		 * @param args:		the list of the pointers to the arguments passed into this method.
		 */
		virtual void Call(void* ret, void* object, std::initializer_list<void*> args)	const = 0;
	};
};//namespace vanir

#endif//_VANIR_ICALL_H_
