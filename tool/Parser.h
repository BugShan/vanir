#ifndef	_VANIR_TOOL_PARSER_H_
#define	_VANIR_TOOL_PARSER_H_

#include "ParserOption.h"
#include "TypeDecl.h"
#include <clang-c/Index.h>
#include <vector>

namespace vanir
{
	namespace tool
	{
		class ClangCursor;
		class Parser final
		{
		public:
			 Parser(const ParserOption& option);
			~Parser(void);

		public:
			void Init(void);
			void Release(void);
			void Parse(void);

		private:
			void EatNamespace(const ClangCursor& cursor);
			void EatClass(const ClangCursor& cursor);
			void EatEnum(const ClangCursor& cursor);
			void WriteToFile(void);

		private:
			ParserOption					mParserOption;
			CXIndex							mpClangIndex;
			CXTranslationUnit				mpClangTranslationUnit;

			std::vector<ClassDecl>			mClassDeclVec;
			std::vector<EnumDecl>			mEnumDeclVec;
			std::vector<TypedefDecl>		mTypedefDeclVec;
		};//class Parser
	};//namespace tool
};//namespace vanir
#endif//_VANIR_TOOL_PARSER_H_
