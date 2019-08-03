#include "stats.h"

HttpRequest ParseRequest(string_view line) {
	while (line[0] == ' ') {
		line.remove_prefix(1);
	}
	size_t pos = 0;
	size_t method_pos = line.find(' ', pos);
	string_view method = line.substr(pos, method_pos - pos);
	pos = method_pos + 1;
	size_t uri_pos = line.find(' ', pos);
	string_view uri = line.substr(pos, uri_pos - pos);
	pos = uri_pos + 1;
	string_view protocol = line.substr(pos, line.npos);
	return { method, uri, protocol };
}

Stats::Stats() {
	methodStats = {
	  {"GET", 0},
	  {"PUT", 0},
	  {"POST", 0},
	  {"DELETE", 0},
	  {"UNKNOWN", 0},
	};

	uriStats = {
	  {"/", 0},
	  {"/order", 0},
	  {"/product", 0},
	  {"/basket", 0},
	  {"/help", 0},
	  {"unknown", 0},
	};
}

void Stats::AddMethod(string_view method) {
	if (method == "GET" || method == "POST" ||
		method == "PUT" || method == "DELETE") {
		methodStats[method]++;
	}
	else {
		methodStats["UNKNOWN"]++;
	}
}


void Stats::AddUri(string_view uri) {
	if (uri == "/" || uri == "/order" ||
		uri == "/product" || uri == "/basket" || uri == "/help") {
		uriStats[uri]++;
	}
	else {
		uriStats["unknown"]++;
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methodStats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uriStats;
}
