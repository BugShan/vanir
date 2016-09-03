#include <vanir/TemplateClass.h>
#include <vanir/Vanir.h>

namespace vanir
{
	TemplateClass::TemplateClass(const std::string& fullname, const std::string& templateName, const unsigned int size)
		: Class(fullname, size)
		, mTemplateName(templateName)
		, mTemplateArgumentNameVec()
	{ ; }
	TemplateClass::~TemplateClass(void)
	{ ; }

	const std::vector<const Type*> TemplateClass::GetTemplateArgumentTypePtrVec(void) const
	{
		std::vector<const Type*> ret;
		for(const auto& argName : mTemplateArgumentNameVec)
		{
			const Type* type_ = vanir::GetTypeByName(argName);
			ret.push_back(type_);
		}
		return ret;
	}

	template<typename T, typename... Args>
	std::vector<std::string> GetTemplateArgumentTypeNameVec(void)
	{
		std::vector<std::string> ret = GetTemplateArgumentTypeNameVec<Args...>();
		std::string& fullname = vanir::type_info<T>::fullname;
		ret.push_back(fullname);
	}
	template<typename T>
	std::vector<std::string> GetTemplateArgumentTypeNameVec(void)
	{
		std::vector<std::string> ret;
		std::string fullname = vanir::type_info<T>::fullname;
		ret.push_back(fullname);
		return ret;
	}
};//namespace vanir
