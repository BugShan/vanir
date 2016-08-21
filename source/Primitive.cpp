#include <vanir/Primitive.h>
#include <vanir/Vanir.h>

#define PRIMITIVE_TYPE_INFO(t)	\
template<>\
const std::string type_info<t>::fullname = #t

namespace vanir
{
	PRIMITIVE_TYPE_INFO(bool);
	PRIMITIVE_TYPE_INFO(char);
	PRIMITIVE_TYPE_INFO(unsigned char);
	PRIMITIVE_TYPE_INFO(short);
	PRIMITIVE_TYPE_INFO(unsigned short);
	PRIMITIVE_TYPE_INFO(int);
	PRIMITIVE_TYPE_INFO(unsigned int);
	PRIMITIVE_TYPE_INFO(long);
	PRIMITIVE_TYPE_INFO(unsigned long);
	PRIMITIVE_TYPE_INFO(long long);
	PRIMITIVE_TYPE_INFO(unsigned long long);
	PRIMITIVE_TYPE_INFO(float);
	PRIMITIVE_TYPE_INFO(double);

	Primitive::Primitive(const std::string& fullName)
		: Type(fullName, Type::TYPE_KIND_PRIMITIVE)
	{ ; }
	Primitive::~Primitive(void)
	{ ; }
};//namespace vanir
