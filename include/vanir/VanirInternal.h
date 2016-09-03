#ifndef	_VANIR_VANIRINTERNAL_H_
#define	_VANIR_VANIRINTERNAL_H_

#include <vanir/Class.h>
#include <vanir/Primitive.h>
#include <vanir/Enum.h>

namespace vanir
{
	class Internal final
	{
	public:
		/**
		 * Register a type into the vanir library.
		 */
		static void RegisterType(const Type* const typePtr);
		
		template<typename T>
		static Type* CreateType(void)
		{
			Type* ret = nullptr;
			const std::string& fullName = type_info<T>::fullName;
			const unsigned int size = sizeof(typename std::remove_pointer<
				typename std::remove_all_extents<T>::type>::type);
			if(std::is_class<T>::value)
				ret = new Class(fullName, size);
			return ret;
		}

		template<typename T>
		static const Type* const RegisterType(void)
		{
			const std::string& fullName = type_info<T>::fullName;
			const Type* ret = GetTypeByName(fullName);
			if(ret) return ret;

			const unsigned int size = sizeof(typename std::remove_pointer<
				typename std::remove_all_extents<T>::type>::type);
			if(std::is_class<T>::value)
				ret = new Class(fullName, size);
			else
				ret = new Primitive(fullName, size);
			RegisterType(ret);
			return ret;
		}
	private:
		Internal(void)	= delete;
	};//class Internal
};//namespace vanir

#endif//_VANIR_VANIRINTERNAL_H_
