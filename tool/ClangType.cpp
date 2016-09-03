#include "ClangType.h"

namespace vanir
{
	namespace tool
	{
		ClangType::ClangType(const CXType& handle)
			: mHandle(handle)
		{ ; }
		ClangType::~ClangType(void)
		{ ; }

		const std::string ClangType::GetKindStr(void) const
		{
			auto cx_str = ::clang_getTypeKindSpelling(this->GetKind());
			auto c_str = ::clang_getCString(cx_str);
			std::string ret(c_str);
			::clang_disposeString(cx_str);
			return ret;
		}
		const std::string ClangType::GetSpelling(void) const
		{
			auto cx_str	= ::clang_getTypeSpelling(mHandle);
			auto c_str	= ::clang_getCString(cx_str);
			std::string ret(c_str);
			::clang_disposeString(cx_str);
			return ret;
		}
	};//namespace tool
};//namespace vanir
