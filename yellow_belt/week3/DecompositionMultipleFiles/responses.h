#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>

struct BusesForStopResponse {
	std::vector<std::string> busesForStops;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
	std::string bus;
	std::vector<std::string> busesForStops;
	std::map<std::string, std::vector<std::string>> stopsForBus;
};


std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	std::map<std::string, std::vector<std::string>> busesForStops;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);