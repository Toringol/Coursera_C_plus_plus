#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
	if (r.busesForStops.empty()) {
		os << "No stop";
	}
	else {
		for (const auto& bus : r.busesForStops) {
			os << bus << " ";
		}
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	if (r.busesForStops.empty())
		os << "No bus";
	else {
		for (const auto& stop : r.busesForStops) {
			os << "Stop " << stop << ": ";
			if (r.stopsForBus.at(stop).size() == 1) {
				os << "no interchange";
			}
			else {
				for (const auto& other_bus : r.stopsForBus.at(stop)) {
					if (other_bus != r.bus) {
						os << other_bus << " ";
					}
				}
			}
			if (&stop != &r.busesForStops.back())
				os << std::endl;
		}
	}

	return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
	if (r.busesForStops.empty()) {
		os << "No buses";
	}
	else {
		for (const auto& bus_item : r.busesForStops) {
			os << "Bus " << bus_item.first << ": ";
			for (const std::string& stop : bus_item.second) {
				os << stop << " ";
			}
			if (bus_item != *(--r.busesForStops.end()))
				os << std::endl;
		}
	}
	return os;
}
