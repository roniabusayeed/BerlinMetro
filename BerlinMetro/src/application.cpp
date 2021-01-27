#include "ui.h"
#include "routes.h"
#include "edge.h"
#include "read.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


int main()
{
	
	

	readConnections();
	Network n;
	UI ui(n);
	
	ui.loop();



	

	
	

	


}
