#ifndef	_ANVIR_TOOL_CLANGTYPE_H_
#define	_ANVIR_TOOL_CLANGTYPE_H_

#include <clang-c/Index.h>
#include <string>

namespace vanir
{
	namespace tool
	{
		class ClangType final
		{
		public:
			explicit ClangType(const CXType& handle);
			~ClangType(void);

		public:
			const std::string GetSpelling(void) const;

		private:
			CXType		mHandle;
		};//class ClangType
	};//namespace tool
};//namespace vanir

#endif//_ANVIR_TOOL_CLANGTYPE_H_
