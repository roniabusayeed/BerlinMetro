#include "ui.h"
#include "routes.h"
#include "edge.h"


#include <iostream>

int main()
{
	Network n;
	UI ui(n);

	ui.loop();
}
