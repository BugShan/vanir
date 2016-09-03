#ifndef	_VANIR_TOOL_DECLARE_H_
#define	_VANIR_TOOL_DECLARE_H_

#include "ClangCursor.h"
#include <string>
#include <vector>

namespace vanir
{
	namespace tool
	{
		class Declare
		{
		public:
			static const bool ContainDecl(const std::string& name);
			static void AddDeclare(const Declare& decl);
			static Declare* GetDeclareByName(const std::string& name);
			static const std::vector<Declare*>& GetAllDeclareVec(void);

		public:
			enum class DeclareKind
			{
				Field,
				Method,
				Class,
				TemplateClass,
				Enum,
			};//enum DeclareKind
		public:
			Declare(const ClangCursor& cursor);
			virtual ~Declare(void);

		public:
			virtual const bool Init(void);
			virtual const Declare::DeclareKind GetKind(void) const = 0;
			const std::string& GetName(void) const;
			const ClangCursor& GetClangCursor(void) const;

		protected:
			const ClangCursor		mCursor;
			std::string				mName;

		private:
			static std::vector<Declare*>	sDeclareVec;
		};//class Declare

		class FieldDecl final : public Declare
		{
		public:
			FieldDecl(const ClangCursor& cursor);
			virtual ~FieldDecl(void) override;

		public:
			const std::string& GetTypeName(void) const;
			const unsigned int GetOffset(void) const;
			virtual const bool Init(void) override;
			virtual const Declare::DeclareKind GetKind(void) const override;
		private:
			std::string			mTypeName;
			unsigned int		muOffset;
		};//class FieldDecl

		class MethodDecl final : public Declare
		{
		public:
			MethodDecl(const ClangCursor& cursor);
			virtual ~MethodDecl(void) override;
		public:
			virtual const bool Init(void) override;
			virtual const Declare::DeclareKind GetKind(void) const override;
		};//class MethodDecl

		class ClassDecl : public Declare
		{
		public:
			ClassDecl(const ClangCursor& cursor);
			virtual ~ClassDecl(void) override;
		public:
			virtual const bool Init(void) override;
			virtual const Declare::DeclareKind GetKind(void) const override;
			const std::vector<std::string>	GetBaseTypeNameVec(void) const;
			const std::vector<FieldDecl*>& GetFieldDeclVec(void) const;
			const std::vector<MethodDecl*>& GetMethodDeclVec(void) const;
			const bool IsRuntimeMarked(void) const;
			const bool IsHeritedFromObject(void) const;

		protected:
			std::vector<std::string>		mBaseTypeNameVec;
			std::vector<FieldDecl*>			mFieldDeclVec;
			std::vector<MethodDecl*>		mMethodDeclVec;
			bool							mbRuntimeMarked;
		};//class Decl

		class TemplateClassDecl final : public ClassDecl
		{
		public:
			TemplateClassDecl(const std::string& fullName, const ClangCursor& cursor);
			virtual ~TemplateClassDecl(void) override;

		public:
			virtual const bool Init(void) override;
			virtual const Declare::DeclareKind GetKind(void) const override;
			const std::string& GetTemplateName(void) const;

		private:
			const std::string					mTemplateName;
		};//class TemplateClassDecl

		class EnumDecl final : public Declare
		{
		public:
			EnumDecl(const ClangCursor& cursor);
			virtual ~EnumDecl(void) override;
		public:
			virtual const bool Init(void) override;
			virtual const Declare::DeclareKind GetKind(void) const override;
		};//class EnumDecl
	};//namespace tool
};//namespace vanir
#endif//_VANIR_TOOL_DECLARE_H_
