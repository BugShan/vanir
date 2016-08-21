#ifndef	_VANIR_MODULE_H_
#define	_VANIR_MODULE_H_

#include <string>

#define VANIR_MODULE(m) m##Module
#define IMPORT_MODULE(m) \
namespace vanir\
{\
	class m##Module final : public vanir::Module\
	{\
	public:\
		m##Module(void);\
		virtual ~m##Module(void) override;\
	public:\
		static m##Module& GetMe(void);\
	public:\
		virtual void Init(void) override;\
	private:\
		static m##Module*		spMyself;\
	};\
}

namespace vanir
{
	class Module
	{
	public:
		Module(const std::string& moduleName);
		virtual ~Module(void);

	public:
		virtual void Init(void) = 0;

	private:
		const std::string			mModuleName;
	};//class Module
};//namespace vanir
#endif//_VANIR_MODULE_H_
