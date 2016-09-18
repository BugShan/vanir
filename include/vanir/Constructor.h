#ifndef	_VANIR_CONSTRUCTOR_H_
#define	_VANIR_CONSTRUCTOR_H_

#include <vanir/ICall.h>
#include <assert.h>
namespace vanir
{
	template<typename Class, typename... Args>
	class Constructor final : public ICall
	{
	public:
		inline Constructor(void);
		virtual ~Constructor(void) override;
	public:
		/**
		 * Get the count of this method's parameter.
		 */
		virtual const unsigned int GetParameterCount(void) const override;
		/**
		 * Call this method.
		 * @param ret:		write the return of this method into ret.
		 * @param object:	the pointer to the object which owns this method.
		 * @param args:		the list of the pointers to the arguments passed into this method.
		 */
		virtual void Call(void* ret, void* object, std::initializer_list<void*> args) const override;
	private:
		template<unsigned... Is>
		inline void DoCall(void* ret, void** args, detail::indices<Is...>) const;
	};//class Constructor

	template<typename Class, typename... Args>
	inline Constructor<Class, Args...>::Constructor(void)
	{ ; }

	template<typename Class, typename... Args>
	Constructor<Class, Args...>::~Constructor<Class, Args...>(void)
	{ ; }

	template<typename Class, typename... Args>
	const unsigned int Constructor<Class, Args...>::GetParameterCount(void) const
	{ return sizeof...(Args); }

	template<typename Class, typename... Args>
	void Constructor<Class, Args...>::Call(void* ret, void* object, std::initializer_list<void*> args) const
	{
		assert(args.size() == sizeof...(Args) && "MethodCall: argument count not matched.");
		this->DoCall(ret, const_cast<void**>(args.begin()), typename detail::unpack<sizeof...(Args)>::indices());
	}

	template<typename Class, typename... Args>
	template<unsigned... Is>
	inline void Constructor<Class, Args...>::DoCall(void* ret, void** args, detail::indices<Is...>) const
	{
		Class* instance = new Class(static_cast<Args>(*(typename std::remove_reference<Args>::type*)args[Is])...);
		memcpy(ret, &instance, sizeof(instance));
	}
};//namespace vanir
#endif//_VANIR_CONSTRUCTOR_H_
