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
	
	
	//********* Just marked as comment temporary for testing readConnections() function below **********
	readConnections();
	Network n;
	UI ui(n);
	
	ui.loop();



	

	
	

	


}
