#include "application.h"
#include "worldgen.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(){
	
	std::string bruh = "amogus";
	scandium::World cock;
	cock.generateWorldSeed(bruh);
	std::cout << cock.getWorldSeed() << "\n";

	scandium::Application app{};
	try
	{
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}