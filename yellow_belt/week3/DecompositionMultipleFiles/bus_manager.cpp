#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
	buses_to_stops[bus] = stops;
	for (const auto& stop : stops)
		stops_to_buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
	BusesForStopResponse response;
	if (stops_to_buses.count(stop)) {
		response.busesForStops = stops_to_buses.at(stop);
	}
	return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
	StopsForBusResponse response;
	if (buses_to_stops.count(bus)) {
		response.bus = bus;
		response.busesForStops = buses_to_stops.at(bus);
		response.stopsForBus = stops_to_buses;
	}
	return response;
}

AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse response;
	if (!buses_to_stops.empty())
		response.busesForStops = buses_to_stops;
	return response;
}