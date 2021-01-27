#pragma once
#include <vector>
#include <string>
#include "routes.h"

class UI
{
public:
	UI(Network& network) : m_network(network) {}
	void loop();

private:

	void listMenuOptions() const;
	unsigned readChoice(std::string msg, unsigned min, unsigned max) const;

	void outputAllConnections();
	void findBestConnection();
	void addTrainConnection();
	Network& m_network;
	std::vector<std::string> m_menu{ "Output all train connections", "Find the best train connection", "Edit train connection data", "Leave Program" };



};
