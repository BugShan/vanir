#ifndef	_TEST_H_
#define	_TEST_H_

#include <vanir/Object.h>
#include "../include/vanir/Object.h"
#include <vector>
#include <stdlib.h>
#include <map>
#include <set>
using namespace vanir;
struct sss
{};
namespace test
{
	class Base{};
	class Test : public vanir::Object
	{
	public:
		Test(void) {}
		void foo(const int& i);
		virtual Type* GetType(void) const override
		{
			return nullptr;
		}
	public:
		int i;
		int j;
		std::vector<int> ivec;
	};
};
#endif//_TEST_H_
