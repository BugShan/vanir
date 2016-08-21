#ifndef	_TEST_H_
#define	_TEST_H_

namespace test
{
	class Base1
	{
	public:
		void foo1(const int);
		int i;
	};//class Base1
	class Base2
	{
	public:
		virtual void foo2(const float);
		float f;
	};
	class Test : public Base1, public Base2
	{
	public:
		virtual void foo2(const float) override;
		char c;
	};//class Test
};//namespace test
#endif//_TEST_H_
