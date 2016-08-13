#include "ClangCursor.h"
#include "ClangType.h"
#include <string>

namespace vanir
{
	namespace tool
	{
		const std::string ClangCursor::GetDisplayName(void) const
		{
			const auto cx_str = ::clang_getCursorDisplayName(mHandle);
			const auto c_str = ::clang_getCString(cx_str);
			const std::string ret(c_str);
			::clang_disposeString(cx_str);
			return ret;
		}
		const std::string ClangCursor::GetSpelling(void) const
		{
			const auto cx_str = ::clang_getCursorSpelling(mHandle);
			const auto c_str = ::clang_getCString(cx_str);
			const std::string ret(c_str);
			::clang_disposeString(cx_str);
			return ret;
		}
		const std::vector<ClangCursor> ClangCursor::GetChildren(void) const
		{
			std::vector<ClangCursor> ret;
			auto visitor = [](CXCursor cursor, CXCursor parent, CXClientData data)
			{
				auto container = static_cast<std::vector<ClangCursor>*>(data);
				container->emplace_back(cursor);
				if(cursor.kind == ::CXCursor_LastPreprocessing)
					return ::CXChildVisit_Break;
				return ::CXChildVisit_Continue;
			};
			::clang_visitChildren(mHandle, visitor, &ret);
			return ret;
		}

		const ClangType ClangCursor::GetClangType(void) const
		{
			return ClangType(::clang_getCursorType(mHandle));
		}
	};//namespace tool
};//namespace vanir
