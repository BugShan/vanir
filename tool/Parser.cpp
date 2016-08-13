#include "Parser.h"
#include "ClangCursor.h"
#include "ClangType.h"
#include "mustache/Mustache.h"

#include <iostream>
#include <fstream>

#define LOG_COLOR_RED	"\033[31m"
#define LOG_COLOR_RESET	"\033[0m"

namespace vanir
{
	namespace tool
	{
		Parser::Parser(const ParserOption& option)
			: mParserOption(option)
			, mpClangIndex(nullptr)
			, mpClangTranslationUnit(nullptr)
			, mClassDeclVec()
			, mEnumDeclVec()
			, mTypedefDeclVec()
		{ ; }
		Parser::~Parser(void)
		{
			this->Release();
		}

		void Parser::Init(void)
		{
			mpClangIndex = ::clang_createIndex(true, mParserOption.displayDiagnostics);
			
			std::vector<const char*>	arguments;
			for(auto& arg : mParserOption.arguments)
				arguments.push_back(arg.c_str());

			mpClangTranslationUnit = ::clang_createTranslationUnitFromSourceFile(mpClangIndex,
																				 mParserOption.inputFile.c_str(),
																				 static_cast<int>(arguments.size()),
																				 arguments.data(),
																				 0,
																				 nullptr);
		}
		void Parser::Release(void)
		{
			if(mpClangTranslationUnit)
			{
				::clang_disposeTranslationUnit(mpClangTranslationUnit);
				mpClangTranslationUnit = nullptr;
			}
			if(mpClangIndex)
			{
				::clang_disposeIndex(mpClangIndex);
				mpClangIndex = nullptr;
			}
			mClassDeclVec.clear();
			mEnumDeclVec.clear();
			mTypedefDeclVec.clear();
		}

		void Parser::Parse()
		{
			ClangCursor cursor(::clang_getTranslationUnitCursor(mpClangTranslationUnit));
			this->EatNamespace(cursor);
			this->WriteToFile();
		}

		void Parser::EatNamespace(const ClangCursor& cursor)
		{
			for(auto& child : cursor.GetChildren())
			{
				auto kind = child.GetKind();
				if(kind == ::CXCursor_Namespace)
				{
					this->EatNamespace(child);
				}
				else if((kind == ::CXCursor_ClassDecl || kind == ::CXCursor_StructDecl)
					 && child.IsDefinition())
				{//the actual definition of a class or a struct
					this->EatClass(child);
				}
				else if(kind == ::CXCursor_EnumDecl && child.IsDefinition())
				{
					this->EatEnum(child);
				}
				else if(kind == ::CXCursor_TypedefDecl)
				{
				}
			}
		}
		void Parser::EatClass(const ClangCursor& cursor)
		{
			ClassDecl decl;
			decl.className = cursor.GetDisplayName();
			decl.fullName = cursor.GetClangType().GetSpelling();
			for(auto& child : cursor.GetChildren())
			{
				switch(child.GetKind())
				{
				case ::CXCursor_CXXBaseSpecifier:
				{
					decl.baseNameVec.push_back(child.GetClangType().GetSpelling());
				}break;
				case ::CXCursor_Constructor:
				{
					//TODO:: constructor
				}break;
				case ::CXCursor_FieldDecl:
				{
					decl.fieldNameVec.push_back(child.GetDisplayName());
				}break;
				case ::CXCursor_VarDecl:
				{
					//TODO:: static field
				}break;
				case ::CXCursor_CXXMethod:
				{
					if(child.IsStaticMethod())
					{
						//TODO:: static method
					}
					else
					{
						decl.methodNameVec.push_back(child.GetSpelling());
					}
				}break;
				case ::CXCursor_EnumDecl:
				{
					//enum defiend within a class
					if(child.IsDefinition())
						this->EatEnum(child);
				}
				default:
					break;
				}
			}
			mClassDeclVec.push_back(decl);
		}
		void Parser::EatEnum(const ClangCursor& cursor)
		{
			const std::string spelling = cursor.GetClangType().GetSpelling();
			//skip anonymous enum
			if(std::string::npos == spelling.find("anonymous enum at"))
			{

			}
		}
		void Parser::WriteToFile(void)
		{
			std::string templateContext;
			{
				std::ifstream input(mParserOption.templateFile);
				if(!input)
				{
					std::cout << LOG_COLOR_RED
							  << mParserOption.templateFile
							  << " not found!"
							  << LOG_COLOR_RESET
							  << std::endl;
					return;
				}
				input.seekg(0, std::ios::beg);
				templateContext.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
				input.close();
			}
			Mustache::Mustache<std::string>	mustacheTemplate(templateContext);

			std::string headerFileName = mParserOption.inputFile;
			std::replace(headerFileName.begin(), headerFileName.end(), '.', '_');
			std::replace(headerFileName.begin(), headerFileName.end(), '/', '_');
			Mustache::Data<std::string> root(Mustache::Data<std::string>::Type::Object);
			root["MODULE_NAME"] = mParserOption.moduleName;
			root["INPUT_HEADER_PATH"] = mParserOption.inputFile;
			root["INPUT_HEADER_NAME"] = headerFileName;

			Mustache::Data<std::string> classNodeList(Mustache::Data<std::string>::Type::List);
			for(auto& classDecl : mClassDeclVec)
			{
				Mustache::Data<std::string> classNode(Mustache::Data<std::string>::Type::Object);
				classNode["CLASS_NAME"] = classDecl.fullName;

				Mustache::Data<std::string> fieldNodeList(Mustache::Data<std::string>::Type::List);
				for(auto& fieldName : classDecl.fieldNameVec)
				{
					Mustache::Data<std::string> fieldNode(Mustache::Data<std::string>::Type::Object);
					fieldNode["CLASS_FIELD_NAME"] = fieldName;
					fieldNodeList << std::move(fieldNode);
				}
				classNode["CLASS_FIELD_LIST"] = std::move(fieldNodeList);

				Mustache::Data<std::string> methodNodeList(Mustache::Data<std::string>::Type::List);
				for(auto& methodName : classDecl.methodNameVec)
				{
					Mustache::Data<std::string> methodNode(Mustache::Data<std::string>::Type::Object);
					methodNode["CLASS_METHOD_NAME"] = methodName;
					methodNodeList << std::move(methodNode);
				}
				classNode["CLASS_METHOD_LIST"] = std::move(methodNodeList);

				classNodeList << std::move(classNode);
			}
			root["CLASS_RUNTIME_LIST"] = std::move(classNodeList);

			{
				std::ofstream output(mParserOption.outputFile);
				output << mustacheTemplate.render(root);
				output.close();
			}
		}

	};//namespace tool
};//namespace vanir
