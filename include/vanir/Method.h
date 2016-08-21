#ifndef	_VANIR_METHOD_H_
#define	_VANIR_METHOD_H_

#include <vanir/ICall.h>

#include <type_traits>
#include <initializer_list>
#include <memory.h>
#include <assert.h>

namespace vanir
{
	namespace detail
	{
		template<unsigned... N>
		struct indices
		{ ; };//struct indices
		template<unsigned N, unsigned... Is>
		struct unpack : public unpack<N - 1, N - 1, Is...>
		{ ; };//struct unpack<N, Is...>
		template<unsigned... Is>
		struct unpack<0, Is...>
		{
			using indices = indices<Is...>;
		};//sturct unpack<0, Is...>
	};//namespace detail

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
		template<typename T, typename = typename std::enable_if<std::is_member_pointer<T>::value, void>::type>
		inline Method(const std::string& name, T methodPtr);
		
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
		inline void Call(void* ret, void* object, std::initializer_list<void*> args = { });

	private:
		const std::string				mName;
		const ICall* const				mpCall;
		//the size of a pointer(x64) is 16.
		// vtable + FunPtr
		unsigned char					mBuffer[32];
	};//class Method

	template<typename T>
	class MethodCall;

	template<typename Class, typename Return, typename... Args>
	class MethodCall<Return(Class::*)(Args...)> final : public ICall
	{
		using FunPtr = Return(Class::*)(Args... args);
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
	template<typename T, typename/* = typename std::enable_if<std::is_member_pointer<T>::value, void>::type*/>
	inline Method::Method(const std::string& name, T methodPtr)
		: mName(name)
		, mpCall((ICall*)mBuffer)
	{
		static_assert(sizeof(mBuffer) >= sizeof(MethodCall<T>), "The size of the buffer is not enough.");
		new(mBuffer)MethodCall<T>(methodPtr);
	}

	inline Method::~Method(void)
	{
		delete mpCall;
	}

	inline const std::string& Method::GetName(void) const
	{ return this->mName; }
	inline const unsigned int Method::GetParameterCount(void) const
	{ return this->mpCall->GetParameterCount(); }

	inline void Method::Call(void* ret, void* object, std::initializer_list<void*> args/* = { }*/)
	{
		this->mpCall->Call(ret, object, args);
	}

	/*===================================class MethodCall===============================*/
	template<typename Class, typename Return, typename... Args>
	inline MethodCall<Return(Class::*)(Args...)>::MethodCall(MethodCall<Return(Class::*)(Args...)>::FunPtr methodPtr)
		: mpFun(methodPtr)
	{ ; }
	template<typename Class, typename Return, typename... Args>
	inline MethodCall<Return(Class::*)(Args...)>::~MethodCall(void)
	{ ; }

	template<typename Class, typename Return, typename... Args>
	const unsigned int MethodCall<Return(Class::*)(Args...)>::GetParameterCount(void) const
	{ return sizeof...(Args); }

	template<typename Class, typename Return, typename... Args>
	void MethodCall<Return(Class::*)(Args...)>::Call(void* ret, void* object, std::initializer_list<void*> args) const
	{
		//assert(args.size() == sizeof...(Args), "MethodCall: argument count not matched.");
		assert(args.size() == sizeof...(Args));
		this->DoCall(ret, object, const_cast<void**>(args.begin()), typename detail::unpack<sizeof...(Args)>::indices());
	}

	template<typename Class, typename Return, typename... Args>
	template<typename T, unsigned... Is>
	inline auto MethodCall<Return(Class::*)(Args...)>::DoCall(void* ret, void* object, void** args, detail::indices<Is...>) const
		-> typename std::enable_if<!std::is_void<T>::value>::type
	{
		Return res = ((static_cast<Class*>(object))->*mpFun)(*(Args*)args[Is]...);
		memcpy(ret, &res, sizeof(res));
	}
	template<typename Class, typename Return, typename... Args>
	template<typename T, unsigned... Is>
	inline auto MethodCall<Return(Class::*)(Args...)>::DoCall(void* ret, void* object, void** args, detail::indices<Is...>) const
		-> typename std::enable_if<std::is_void<T>::value>::type
	{
		((static_cast<Class*>(object))->*mpFun)(*(Args*)args[Is]...);
	}
};//namespace vanir
#endif//_VANIR_METHOD_H_
