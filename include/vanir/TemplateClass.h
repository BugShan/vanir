#ifndef	_VANIR_TEMPLATECLASS_H_
#define	_VANIR_TEMPLATECLASS_H_
#include <vanir/Class.h>

namespace vanir
{
	class TemplateClass final : public Class
	{
		friend class Internal;
	public:
		inline const std::string& GetTemplateName(void) const;
		inline const std::vector<std::string>& GetTemplateArgumentNameVec(void) const;

	public:
		void DefineTemplateArgument(const std::string& argName);
		const std::vector<const Type*> GetTemplateArgumentTypePtrVec(void) const;

	private:
		TemplateClass(const std::string& fullname, const std::string& templateName, const unsigned int size);
		virtual ~TemplateClass(void);
	private:
		const std::string				mTemplateName;
		std::vector<std::string>		mTemplateArgumentNameVec;
	};//class TemplateClass
	inline const std::string& TemplateClass::GetTemplateName(void) const
	{ return mTemplateName; }
	inline const std::vector<std::string>& TemplateClass::GetTemplateArgumentNameVec(void) const
	{ return mTemplateArgumentNameVec; }
};//namespace vanir
#endif//_VANIR_TEMPLATECLASS_H_
