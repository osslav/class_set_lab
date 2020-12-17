#include "set.h"

int main()
{
	try
	{
		Set test;
		
		test += -128;
		test = test + -128 + 127 + 33 + 0;
		std::cout << (int)test.searchMax() << '\n';
		std::cout << (int)test.searchMin() << '\n';
		test = test - 0;
		test -= 33;
		std::cout << (int)test.searchMax() << '\n';
		std::cout << (int)test.searchMin() << '\n';

		return 0;
	}
	catch (ErrorCodeBoolVector err)
	{
		std::cout << "Error " << err << " in method BoolVector\n";
		return err;
	}
}
