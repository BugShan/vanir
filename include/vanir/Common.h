#ifndef _VANIR_COMMON_H_
#define	_VANIR_COMMON_H_

#if defined(_VANIR_PARSER_)
	#define RUNTIME __attribute__((annotate("VanirRuntime")))
#else
	#define RUNTIME
#endif//defined(_VANIR_PARSER_)

namespace vanir
{
	typedef unsigned int type_id;
};//namespace vanir

#endif//_VANIR_COMMON_H_
