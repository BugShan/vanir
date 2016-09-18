#include "test.h"
#include <iostream>
#include <vanir/Vanir.h>
#include <vanir/Type.h>
#include <vanir/Class.h>
#include <vanir/Field.h>
#include <vanir/Method.h>

namespace test
{
	void Test::foo(const int& i)
	{
		this->i  = i;
		this->j = i * 2;
	}
};

IMPORT_MODULE(Test);

using namespace vanir;
using namespace test;
int main(void)
{
	vanir::InitVanir();
	vanir::LoadModule(TestModule::GetMe());
	
	std::cout << "Vanir Test" << std::endl;
	const auto& type_list = vanir::GetAllTypeList();
	for(const auto typePtr : type_list)
	{
		std::cout << typePtr->GetFullName() << std::endl;
		if(typePtr->IsClass())
		{
			const Class* classPtr = static_cast<const Class*>(typePtr);
			for(auto fieldPtr : classPtr->GetFieldPtrVec())
				std::cout << fieldPtr->GetName() << std::endl;
			for(auto methodPtr : classPtr->GetMethodPtrVec())
				std::cout << methodPtr->GetName() << std::endl;
		}
	}
	auto* testClass = static_cast<const Class*>(vanir::GetType<test::Test>());
	auto* methodPtr = const_cast<Method*>(testClass->GetMethodPtr("foo"));

	int c = 11;
	Test* t = static_cast<Test*>(testClass->CreateInstance({&c}));

	std::cout << t->i << std::endl;
	int i = 22;
	int j = 2;
	methodPtr->Call(nullptr, t, { &i });
	std::cout << t->i << std::endl;
	return 0;
}
