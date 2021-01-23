#include "ui.h"
#include "routes.h"
#include "edge.h"
#include "filemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>


#include <iostream>

int main()
{
	Network n;
	UI ui(n);

	ui.loop();



}
