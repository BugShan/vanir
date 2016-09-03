#include "test.h"
#include <iostream>
#include <vanir/Vanir.h>
#include <vanir/Type.h>
#include <vanir/Class.h>
#include <vanir/Field.h>
#include <vanir/Method.h>

namespace test
{
	void Test::foo(void)
	{}
};

IMPORT_MODULE(Test);

using namespace vanir;
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
	return 0;
}
