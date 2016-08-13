#ifndef	_VANIR_TOOL_UTILS_H_
#define	_VANIR_TOOL_UTILS_H_

#include <string>

namespace vanir
{
	namespace tool
	{
		namespace utils
		{
			std::string ReplaceAll(const std::string& str, const char* const symbols);
		};//namespace utils
	};//namespace tool
};//namespace vanir

#endif//_VANIR_TOOL_UTILS_H_
