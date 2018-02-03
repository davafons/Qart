#include <iostream>

#include "Qart.h"

int main(int argc, char * argv[])
{
	try
	{
		Qart quart;
		quart.execute();

	}
	catch (const char * msg)
	{
		std::cerr << "Error: " << msg << std::endl;
		return 1;
	}
	
	return 0;
}