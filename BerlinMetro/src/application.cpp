#include "ui.h"
#include "routes.h"
#include "edge.h"


#include <iostream>

int main()
{
	std::cout << "This line is added by Roni." << std::endl;
	Network n;
	UI ui(n);

	ui.loop();
}
