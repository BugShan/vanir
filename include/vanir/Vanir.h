#ifndef	_VANIR_VANIR_H_
#define	_VANIR_VANIR_H_

#include <vanir/Common.h>
#include <vanir/Type.h>
#include <vanir/Class.h>
#include <vanir/Enum.h>
#include <string>
#include <vector>

#if defined(_VANIR_PARSER_)
	#define RUNTIME __attribute__((annotate("Runtime")))
#else
	#define RUNTIME
#endif//defined(_VANIR_PARSER_)

#define TYPE_ID(type) vanir::GetTypeID<##type>()

namespace vanir
{
	template<typename T>
	const type_id GetTypeID(void);

	const Type* const GetTypeByID(const type_id id);

	const Type* const GetTypeByName(const std::string& name);

	const std::vector<const Type*>& GetAllTypeList(void);

	void RegisterType(const Type* const typePtr);
};//namespace vanir
#endif//_VANIR_VANIR_H_
