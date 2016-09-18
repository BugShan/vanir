#include "Parser.h"
#include "ClangCursor.h"
#include "ClangType.h"
#include "Declare.h"
#include "mustache/Mustache.h"

#include <iostream>
#include <fstream>

const char* const LOG_COLOR_RED				= "\033[31m";
const char* const LOG_COLOR_RESET			= "\033[0m";

namespace vanir
{
	namespace tool
	{
		Parser::Parser(const ParserOption& option)
			: mParserOption(option)
			, mpClangIndex(nullptr)
			, mArguments()
		{ ; }
		Parser::~Parser(void)
		{
			this->Release();
		}

		void Parser::Init(void)
		{
			mpClangIndex = ::clang_createIndex(true, mParserOption.displayDiagnostics);
			
			for(auto& arg : mParserOption.arguments)
				mArguments.push_back(arg.c_str());
		}
		void Parser::Release(void)
		{
			if(mpClangIndex)
			{
				::clang_disposeIndex(mpClangIndex);
				mpClangIndex = nullptr;
			}
			mArguments.clear();
		}

		void Parser::Parse()
		{
			for(const auto& input : mParserOption.inputFileList)
			{
				auto clangTranslationUnit = ::clang_createTranslationUnitFromSourceFile(mpClangIndex,
																						input.c_str(),
																						mArguments.size(),
																						mArguments.data(),
																						0,
																						nullptr);
				ClangCursor cursor(::clang_getTranslationUnitCursor(clangTranslationUnit));
				this->EatNamespace(cursor);
				::clang_disposeTranslationUnit(clangTranslationUnit);
			}
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
				else if((kind == ::CXCursor_ClassDecl || kind == ::CXCursor_StructDecl))
				{
					if(child.IsDefinition())
						this->EatClass(child);
					else
						this->EatExternalClass(child);
				}
				else if(kind == ::CXCursor_ClassTemplate)
				{
					if(child.IsDefinition())
						this->EatTemplateClass(child);
					else
						this->EatExternalClass(child);
				}
				else if(kind == ::CXCursor_EnumDecl && child.IsDefinition())
				{
					this->EatEnum(child);
				}
				else if(kind == ::CXCursor_TypedefDecl || cursor.GetKind() == ::CXCursor_TypeAliasDecl)
				{
				}
			}
		}
		void Parser::EatClass(const ClangCursor& cursor)
		{
			ClassDecl* declPtr = new ClassDecl(cursor);
			if(declPtr->Init())
				Declare::AddDeclare(*declPtr);
		}
		void Parser::EatTemplateClass(const ClangCursor& cursor)
		{ ; }
		void Parser::EatExternalClass(const ClangCursor& cursor)
		{ ; }
		void Parser::EatEnum(const ClangCursor& cursor)
		{
			EnumDecl* declPtr = new EnumDecl(cursor);
			if(declPtr->Init())
				Declare::AddDeclare(*declPtr);
		}
		void Parser::WriteToFile(void)
		{
			//read mustache template file
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

			//write mustache tree data
			Mustache::Data<std::string> root(Mustache::Data<std::string>::Type::Object);
			root["MODULE_NAME"] = mParserOption.moduleName;
			{//header list
				Mustache::Data<std::string> headerListNode(Mustache::Data<std::string>::Type::List);
				for(const auto& header : mParserOption.inputFileList)
				{
					Mustache::Data<std::string> headerNode(Mustache::Data<std::string>::Type::Object);
					headerNode["HEADER"] = header;
					headerListNode << std::move(headerNode);
				}
				root["HEADER_LIST"] = std::move(headerListNode);
			}
			{//type info list
				Mustache::Data<std::string> typeInfoListNode(Mustache::Data<std::string>::Type::List);
				for(const auto* declPtr : Declare::GetAllDeclareVec())
				{
					Mustache::Data<std::string> typeInfoNode(Mustache::Data<std::string>::Type::Object);
					typeInfoNode["TYPE_NAME"] = declPtr->GetName();
					typeInfoListNode << std::move(typeInfoNode);
				}
				root["TYPE_INFO_LIST"] = std::move(typeInfoListNode);
			}
			{//class list
				Mustache::Data<std::string> classListNode(Mustache::Data<std::string>::Type::List);
				for(const auto* declPtr : Declare::GetAllDeclareVec())
				{
					if(declPtr->GetKind() != Declare::DeclareKind::Class || declPtr->GetKind() == Declare::DeclareKind::TemplateClass)
						continue;
					const ClassDecl* classDeclPtr = static_cast<const ClassDecl*>(declPtr);
					Mustache::Data<std::string> classNode(Mustache::Data<std::string>::Type::Object);
					classNode["CLASS_NAME"] = classDeclPtr->GetName();
					classNode["CLASS_CONSTRUCTOR_SIGN"] = classDeclPtr->GetConstructorSignature();

					Mustache::Data<std::string> fieldListNode(Mustache::Data<std::string>::Type::List);
					for(const auto* fieldDeclPtr : classDeclPtr->GetFieldDeclVec())
					{
						Mustache::Data<std::string> fieldNode(Mustache::Data<std::string>::Type::Object);
						fieldNode["CLASS_FIELD_TYPE_NAME"]	= fieldDeclPtr->GetTypeName();
						fieldNode["CLASS_FIELD_NAME"]		= fieldDeclPtr->GetName();
						fieldNode["CLASS_FIELD_OFFSET"]		= std::to_string(fieldDeclPtr->GetOffset());
						fieldListNode << std::move(fieldNode);
					}
					classNode["CLASS_FIELD_LIST"] = std::move(fieldListNode);

					Mustache::Data<std::string> methodListNode(Mustache::Data<std::string>::Type::List);
					for(const auto* methodDeclPtr : classDeclPtr->GetMethodDeclVec())
					{
						Mustache::Data<std::string> methodNode(Mustache::Data<std::string>::Type::Object);
						methodNode["CLASS_METHOD_NAME"] = methodDeclPtr->GetName();
						methodListNode << std::move(methodNode);
					}
					classNode["CLASS_METHOD_LIST"] = std::move(methodListNode);
					classListNode << std::move(classNode);
				}
				root["CLASS_LIST"] = std::move(classListNode);
			}
			{//write to file
				std::ofstream output(mParserOption.outputFile);
				output << mustacheTemplate.render(root);
				output.close();
			}
		}
	};//namespace tool
};//namespace vanir
