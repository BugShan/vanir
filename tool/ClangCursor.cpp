#include "ClangCursor.h"
#include "ClangType.h"
#include <string>

namespace vanir
{
	namespace tool
	{
		const std::string ClangCursor::GetKindStr(void) const
		{
			const auto cx_str = ::clang_getCursorKindSpelling(this->GetKind());
			const auto c_str = ::clang_getCString(cx_str);
			const std::string ret(c_str);
			::clang_disposeString(cx_str);
			return ret;
		}
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
		const ClangCursor ClangCursor::GetParentCursor(void) const
		{
			return ClangCursor(::clang_getCursorSemanticParent(this->mHandle));
		}
		const CX_CXXAccessSpecifier ClangCursor::GetAccessSpecifier(void) const
		{
			return ::clang_getCXXAccessSpecifier(mHandle);
		}
		const unsigned int ClangCursor::GetFieldOffset(void) const
		{
			//clang_Type_getOffsetOf return offset as bit
			return ::clang_Type_getOffsetOf(
				this->GetParentCursor().GetClangType().GetHandle(),
				this->GetDisplayName().c_str()
				) / 8;
		}
		const ClangCursor ClangCursor::GetDeclareCursor(void) const
		{
			auto cx_cursor = ::clang_getTypeDeclaration(this->GetClangType().GetHandle());
			return ClangCursor(cx_cursor);
		}

		const ClangType ClangCursor::GetClangType(void) const
		{
			return ClangType(::clang_getCanonicalType(::clang_getCursorType(mHandle)));
		}
		const ClangType ClangCursor::GetTypedefUnderlyingType(void) const
		{
			return ClangType(::clang_getTypedefDeclUnderlyingType(mHandle));
		}
		const std::string ClangCursor::GetFunctionArgsStr(void) const
		{
			std::string ret;
			const int argCount = ::clang_Cursor_getNumArguments(this->mHandle);
			for(int i = 0; i < argCount; ++ i)
			{
				const ClangCursor cursor = ClangCursor(::clang_Cursor_getArgument(this->mHandle, i));
				ret.append(", ");
				ret.append(cursor.GetClangType().GetSpelling());
			}
			return ret;
		}
	};//namespace tool
};//namespace vanir
