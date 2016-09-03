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
			inline const CXType& GetHandle(void) const;
			inline const CXTypeKind GetKind(void) const;
		public:
			const std::string GetKindStr(void) const;
			const std::string GetSpelling(void) const;

		private:
			CXType		mHandle;
		};//class ClangType
		inline const CXType& ClangType::GetHandle(void) const
		{
			return this->mHandle;
		}
		inline const CXTypeKind ClangType::GetKind(void) const
		{
			return mHandle.kind;
		}
	};//namespace tool
};//namespace vanir

#endif//_ANVIR_TOOL_CLANGTYPE_H_
