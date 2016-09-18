#ifndef	_TEST_H_
#define	_TEST_H_

#include <vanir/Object.h>
using namespace vanir;
namespace test
{
	class Test : public vanir::Object
	{
	public:
		Test(const int& i) { this->i = i; this->j = 1; }
		void foo(const int& i);
		virtual Type* GetType(void) const override
		{
			return nullptr;
		}
	public:
		int i;
		int j;
	};
};
#endif//_TEST_H_
