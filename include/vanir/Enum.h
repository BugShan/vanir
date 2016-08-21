#ifndef	_VANIR_ENUM_H_
#define	_VANIR_ENUM_H_

#include <vanir/Type.h>
#include <vector>
#include <map>

namespace vanir
{
	class Enum final : public Type
	{
	public:
		Enum(const std::string& name);
		virtual ~Enum(void) override;

	public:
		const std::vector<std::string>	GetKeys(void) const;
		const unsigned int GetValue(const std::string& key) const;

	private:
		std::map<std::string, const unsigned int>			mKeyValue;
	};//class Enum
};//namespace vanir
#endif//_VANIR_ENUM_H_
