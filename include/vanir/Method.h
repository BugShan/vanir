#ifndef	_VANIR_METHOD_H_
#define	_VANIR_METHOD_H_

#include <vanir/ICall.h>

#include <type_traits>
#include <initializer_list>
#include <memory.h>
#include <assert.h>

namespace vanir
{
	class Method final
	{
	public:
		/**
		 * The constructor accepting member function pointer.
		 * #param methodName:	the name of the method.
		 * #param methodPtr:	the pointer to the method[Return(Class::*)(Arg...)].
		 * ```
		 *	struct Test
		 *	{
		 *		int foo(int, int);
		 *	};
		 *	Method method("foo", &Test::foo);
		 * ```
		 */
		template<typename Class, typename Return, typename... Args>
		inline Method(const std::string& name, Return(Class::*methodPtr)(Args...));
		template<typename Class, typename Return, typename... Args>
		inline Method(const std::string& name, Return(Class::*methodPtr)(Args...)const);
		
		/**
		 * The destructor.
		 */
		inline ~Method(void);
	public:
		/**
		 * Get the name of this method.
		 * @return:	[std::string]
		 */
		inline const std::string& GetName(void) const;
		/**
		 * Get the count of this method's parameter.
		 */
		inline const unsigned int GetParameterCount(void) const;

	public:
		/**
		 * Call this method.
		 * @param ret:		write the return of this method into ret.
		 * @param object:	the pointer to the object which owns this method.
		 * @param args:		the list of the pointers to the arguments passed into this method.
		 */
		inline void Call(void* ret, void* object, std::initializer_list<void*> args = { }) const;

	private:
		const std::string				mName;
		const ICall* const				mpCall;
		//the size of a pointer(x64) is 16.
		// vtable + FunPtr
		unsigned char					mBuffer[32];
	};//class Method

	template<typename FunPtr, typename Class, typename Return, typename... Args>
	class MethodCall final : public ICall
	{
	public:
		/**
		 * The constructor & the destructor.
		 */
		inline  MethodCall(FunPtr methodPtr);
		virtual ~MethodCall(void) override;
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
		virtual void Call(void* ret, void* object, std::initializer_list<void*> args)	const override;

	private:
		template<typename T = Return, unsigned... Is>
		inline auto DoCall(void* ret, void* object, void** args, detail::indices<Is...>) const
			-> typename std::enable_if<!std::is_void<T>::value>::type;
		template<typename T = Return, unsigned... Is>
		inline auto DoCall(void* ret, void* object, void** args, detail::indices<Is...>) const
			-> typename std::enable_if<std::is_void<T>::value>::type;

	private:
		const FunPtr				mpFun;
	};//class MethodCall

	/*===================================class Method===============================*/
	template<typename Class, typename Return, typename... Args>
	inline Method::Method(const std::string& name, Return(Class::*methodPtr)(Args...))
		: mName(name)
		, mpCall((ICall*)mBuffer)
	{
		using MethodCallTy = MethodCall<Return(Class::*)(Args...), Class, Return, Args...>;
		static_assert(sizeof(mBuffer) >= sizeof(MethodCallTy), "The size of the buffer is not enough.");
		new(mBuffer)MethodCallTy(methodPtr);
	}
	template<typename Class, typename Return, typename... Args>
	inline Method::Method(const std::string& name, Return(Class::*methodPtr)(Args...)const)
		: mName(name)
		, mpCall((ICall*)mBuffer)
	{
		using MethodCallTy = MethodCall<Return(Class::*)(Args...)const, Class, Return, Args...>;
		static_assert(sizeof(mBuffer) >= sizeof(MethodCallTy), "The size of the buffer is not enough.");
		new(mBuffer)MethodCallTy(methodPtr);
	}

	inline Method::~Method(void)
	{
		delete mpCall;
	}

	inline const std::string& Method::GetName(void) const
	{ return this->mName; }
	inline const unsigned int Method::GetParameterCount(void) const
	{ return this->mpCall->GetParameterCount(); }

	inline void Method::Call(void* ret, void* object, std::initializer_list<void*> args/* = { }*/) const
	{
		this->mpCall->Call(ret, object, args);
	}

	/*===================================class MethodCall===============================*/
	template<typename FunPtr, typename Class, typename Return, typename... Args>
	inline MethodCall<FunPtr, Class, Return, Args...>::MethodCall(const FunPtr methodPtr)
		: mpFun(methodPtr)
	{ ; }
	template<typename FunPtr, typename Class, typename Return, typename... Args>
	inline MethodCall<FunPtr, Class, Return, Args...>::~MethodCall(void)
	{ ; }

	template<typename FunPtr, typename Class, typename Return, typename... Args>
	const unsigned int MethodCall<FunPtr, Class, Return, Args...>::GetParameterCount(void) const
	{ return sizeof...(Args); }

	template<typename FunPtr, typename Class, typename Return, typename... Args>
	void MethodCall<FunPtr, Class, Return, Args...>::Call(void* ret, void* object, std::initializer_list<void*> args) const
	{
		assert(args.size() == sizeof...(Args) && "MethodCall: argument count not matched.");
		this->DoCall(ret, object, const_cast<void**>(args.begin()), typename detail::unpack<sizeof...(Args)>::indices());
	}

	template<typename FunPtr, typename Class, typename Return, typename... Args>
	template<typename T, unsigned... Is>
	inline auto MethodCall<FunPtr, Class, Return, Args...>::DoCall(void* ret, void* object, void** args, detail::indices<Is...>) const
		-> typename std::enable_if<!std::is_void<T>::value>::type
	{
		Return res = ((static_cast<Class*>(object))->*mpFun)(
			static_cast<Args>(*(typename std::remove_reference<Args>::type*)args[Is])...);
		memcpy(ret, &res, sizeof(res));
	}
	template<typename FunPtr, typename Class, typename Return, typename... Args>
	template<typename T, unsigned... Is>
	inline auto MethodCall<FunPtr, Class, Return, Args...>::DoCall(void* ret, void* object, void** args, detail::indices<Is...>) const
		-> typename std::enable_if<std::is_void<T>::value>::type
	{
		((static_cast<Class*>(object))->*mpFun)(
			static_cast<Args>(*(typename std::remove_reference<Args>::type*)args[Is])...);
	}
};//namespace vanir
#endif//_VANIR_METHOD_H_
