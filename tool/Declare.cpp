#include "Declare.h"
#include "ClangType.h"

namespace vanir
{
	namespace tool
	{
		const char* const RUNTIME_ANNOTATE_ATTR		= "VanirRuntime";
		const char* const VANIR_OBJECT_FULLNAME		= "vanir::Object";

		const std::string GetTemplateName(const std::string& name)
		{
			auto found = name.find('<', 0);
			if(found == std::string::npos)
				return "";
			return name.substr(0, found);
		}
		const std::vector<std::string> GetTemlateArgumentNames(const std::string& name)
		{
			std::vector<std::string> ret;
			auto found = name.find('<', 0) + 1;
			while(found != std::string::npos && found < name.size())
			{
				auto next = name.find(',', found);
				if(next == std::string::npos)
					next = name.find('>', found);
				ret.push_back(name.substr(found, next - found));
				found = next + 1;
			}
			return ret;
		}

		std::vector<Declare*> Declare::sDeclareVec;
		const bool Declare::ContainDecl(const std::string& name)
		{
			for(const auto* declPtr : sDeclareVec)
			{
				if(declPtr->GetName() == name)
					return true;
			}
			return false;
		}
		void Declare::AddDeclare(const Declare& decl)
		{
			sDeclareVec.push_back(const_cast<Declare*>(&decl));
		}
		Declare* Declare::GetDeclareByName(const std::string& name)
		{
			for(auto* declPtr : sDeclareVec)
			{
				if(declPtr->GetName() == name)
					return declPtr;
			}
			return nullptr;
		}
		const std::vector<Declare*>& Declare::GetAllDeclareVec(void)
		{
			return sDeclareVec;
		}

		Declare::Declare(const ClangCursor& cursor)
			: mCursor(cursor)
			, mName("")
		{ ; }
		Declare::~Declare(void)
		{ ; }
		const bool Declare::Init(void)
		{
			return true;
		}

		FieldDecl::FieldDecl(const ClangCursor& cursor)
			: Declare(cursor)
			, mTypeName()
		{ ; }
		FieldDecl::~FieldDecl(void)
		{ ; }
		const std::string& FieldDecl::GetTypeName(void) const
		{ return this->mTypeName; }
		const unsigned int FieldDecl::GetOffset(void) const
		{ return this->muOffset; }
		const bool FieldDecl::Init(void)
		{
			this->mName		= this->mCursor.GetDisplayName();
			this->mTypeName	= this->mCursor.GetClangType().GetSpelling();
			this->muOffset	= this->mCursor.GetFieldOffset();
			return true;
		}
		const Declare::DeclareKind FieldDecl::GetKind(void) const
		{
			return Declare::DeclareKind::Field;
		}
		const std::string& Declare::GetName(void) const
		{ return this->mName; }
		const ClangCursor& Declare::GetClangCursor(void) const
		{ return this->mCursor; }

		MethodDecl::MethodDecl(const ClangCursor& cursor)
			: Declare(cursor)
		{ ; }
		MethodDecl::~MethodDecl(void)
		{ ; }
		const bool MethodDecl::Init(void)
		{
			this->mName = this->mCursor.GetSpelling();
			return true;
		}
		const Declare::DeclareKind MethodDecl::GetKind(void) const
		{
			return Declare::DeclareKind::Method;
		}

		ClassDecl::ClassDecl(const ClangCursor& cursor)
			: Declare(cursor)
			, mBaseTypeNameVec()
			, mFieldDeclVec()
			, mMethodDeclVec()
			, mbRuntimeMarked(false)
		{ ; }
		ClassDecl::~ClassDecl(void)
		{
			for(auto* declPtr : mFieldDeclVec)
				delete declPtr;
			for(auto* declPtr : mMethodDeclVec)
				delete declPtr;
		}
		const bool ClassDecl::Init(void)
		{
			this->mName = this->mCursor.GetClangType().GetSpelling();
			if(ContainDecl(this->mName)) return false;
			for(auto& child : this->GetClangCursor().GetChildren())
			{
				if(child.GetKind() == ::CXCursor_CXXBaseSpecifier)
				{
					std::string baseTypeName = child.GetClangType().GetSpelling();
					this->mBaseTypeNameVec.push_back(std::move(baseTypeName));
				}
				else if(child.GetKind() == ::CXCursor_FieldDecl)
				{
					FieldDecl* declPtr = new FieldDecl(child);
					if(declPtr->Init())
						mFieldDeclVec.push_back(declPtr);
					std::string fullTypeName = declPtr->GetClangCursor().GetClangType().GetSpelling();
					std::string templateName = GetTemplateName(fullTypeName);
					if(!Declare::ContainDecl(fullTypeName) && !templateName.empty())
					{
						TemplateClassDecl* templateDeclPtr = new TemplateClassDecl(fullTypeName, declPtr->GetClangCursor().GetDeclareCursor());
						Declare::AddDeclare(*templateDeclPtr);
					}
				}
				else if(child.GetKind() == ::CXCursor_CXXMethod)
				{
					if(child.GetAccessSpecifier() == ::CX_CXXAccessSpecifier::CX_CXXPublic)
					{
						MethodDecl* declPtr = new MethodDecl(child);
						if(declPtr->Init())
							mMethodDeclVec.push_back(declPtr);
					}
				}
				else if(child.GetKind() == ::CXCursor_EnumDecl)
				{
					Declare* declPtr = new EnumDecl(child);
					if(declPtr->Init())
						Declare::AddDeclare(*declPtr);
				}
				else if(child.GetKind() == ::CXCursor_AnnotateAttr)
				{
					if(child.GetDisplayName() == RUNTIME_ANNOTATE_ATTR)
						this->mbRuntimeMarked = true;
				}
			}
			return true;
		}
		const Declare::DeclareKind ClassDecl::GetKind(void) const
		{
			return Declare::DeclareKind::Class;
		}
		const std::vector<std::string> ClassDecl::GetBaseTypeNameVec(void) const
		{ return this->mBaseTypeNameVec; }
		const std::vector<FieldDecl*>& ClassDecl::GetFieldDeclVec(void) const
		{ return this->mFieldDeclVec; }
		const std::vector<MethodDecl*>& ClassDecl::GetMethodDeclVec(void) const
		{ return this->mMethodDeclVec; }
		const bool ClassDecl::IsRuntimeMarked(void) const
		{
			return this->mbRuntimeMarked;
		}
		const bool ClassDecl::IsHeritedFromObject(void) const
		{
			for(const auto& baseTypeName : mBaseTypeNameVec)
			{
				if(baseTypeName == VANIR_OBJECT_FULLNAME) return true;
				const ClassDecl* baseDeclPtr = static_cast<const ClassDecl*>(Declare::GetDeclareByName(baseTypeName));
				if(baseDeclPtr && baseDeclPtr->IsHeritedFromObject())
					return true;
			}
			return false;
		}

		TemplateClassDecl::TemplateClassDecl(const std::string& fullName, const ClangCursor& cursor)
			: ClassDecl(cursor)
			, mTemplateName("")
		{
			this->mName = fullName;
		}
		TemplateClassDecl::~TemplateClassDecl(void)
		{ ; }
		const bool TemplateClassDecl::Init(void)
		{
			return true;
		}
		const Declare::DeclareKind TemplateClassDecl::GetKind(void) const
		{
			return Declare::DeclareKind::TemplateClass;
		}

		EnumDecl::EnumDecl(const ClangCursor& cursor)
			: Declare(cursor)
		{ ; }
		EnumDecl::~EnumDecl(void)
		{ ; }
		const bool EnumDecl::Init(void)
		{
			const std::string spelling = this->GetClangCursor().GetClangType().GetSpelling();
			//skip anonymous enum
			if(std::string::npos == spelling.find("anonymous enum at"))
			{
				this->mName = spelling;
				if(Declare::ContainDecl(this->mName))
					return false;
				return true;
			}
			return false;
		}
		const Declare::DeclareKind EnumDecl::GetKind(void) const
		{
			return Declare::DeclareKind::Enum;
		}
	};//namespace tool
};//namespace vanir
