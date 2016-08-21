#ifndef	_VANIR_TOOL_CLANGCURSOR_H_
#define	_VANIR_TOOL_CLANGCURSOR_H_

#include <clang-c/Index.h>
#include <vector>

namespace vanir
{
	namespace tool
	{
		class ClangType;
		class ClangCursor final
		{
		public:
			inline explicit ClangCursor(const CXCursor& handle);
			inline ~ClangCursor(void);

		public:
			inline const CXCursorKind GetKind(void)	const;
			inline const bool	IsDefinition(void)	const;
			inline const bool	IsConstMethod(void)	const;
			inline const bool	IsStaticMethod(void)const;

		public:
			const std::string GetDisplayName(void) const;
			const std::string GetSpelling(void) const;
			const std::vector<ClangCursor> GetChildren(void) const;
			const ClangType	GetClangType(void) const;

		private:
			CXCursor			mHandle;
		};//class ClangCursor

		inline ClangCursor::ClangCursor(const CXCursor& handle)
			: mHandle(handle)
		{ ; }
		inline ClangCursor::~ClangCursor(void)
		{ ; }

		inline const CXCursorKind ClangCursor::GetKind(void) const
		{
			return mHandle.kind;
		}
		inline const bool ClangCursor::IsDefinition(void) const
		{
			return ::clang_isCursorDefinition(mHandle);
		}
		inline const bool ClangCursor::IsConstMethod(void) const
		{
			return ::clang_CXXMethod_isConst(mHandle);
		}
		inline const bool ClangCursor::IsStaticMethod(void) const
		{
			return ::clang_CXXMethod_isStatic(mHandle);
		}
	};//namespace tool
};//namespace vanir

#endif//_VANIR_TOOL_CLANGCURSOR_H_