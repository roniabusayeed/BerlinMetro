#include "filemanager.h"

#include <iostream>
#include <fstream>
#include "Node.h"
#include "edge.h"


void FileManager::readFromFile()
{

	std::ifstream input_stream("Berlin.txt", std::ifstream::in);
	std::string readTrain, readOrigin, readDestination;
	double readDuration, readDistance;
	while (input_stream >> readTrain >> readOrigin >> readDestination >> readDistance >> readDuration) {
		std::cout << readTrain << " " << readOrigin << " -> " << readDestination << " " << readDistance << " " << readDuration << '\n';
	}
	input_stream.close();
}