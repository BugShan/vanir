#ifndef	_VANIR_TOOL_TYPEDECL_H_
#define	_VANIR_TOOL_TYPEDECL_H_

#include <string>
#include <vector>

namespace vanir
{
	namespace tool
	{
		struct ClassDecl final
		{
			std::string		className;
			std::string		fullName;

			std::vector<std::string>	baseNameVec;
			std::vector<std::string>	fieldNameVec;
			std::vector<std::string>	methodNameVec;
		};//struct ClassDecl

		struct TypedefDecl final
		{
			std::string		className;
			std::string		typeDefName;
		};//struct TypedefDecl

		struct EnumDecl final
		{
			std::string		enumName;
			std::string		fullName;

			std::vector<std::string>	keyNameVec;
		};//struct EnumDecl
		
		void AddClassDecl(const struct ClassDecl& classDecl);
		void AddEnumDecl(const struct EnumDecl& enumDecl);


		void ClearAllCache(void);
	};//namespace tool
};//namespace vanir

#endif//_VANIR_TOOL_TYPEDECL_H_
