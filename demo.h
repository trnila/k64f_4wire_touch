#pragma once
#include <vector>
#include "Utils.h"

class DemoPositions {
public:
	DemoPositions() {
		clear();
	}

	void clear() {
		positions.clear();
		pos = 0;
	}

	void add(Vectorf point) {
		positions.push_back(point);
	}

	bool empty() {
		return positions.empty();
	}

	Vectorf current() {
		return positions[pos];
	}

	Vectorf next() {
		Vectorf ret = positions[pos];
		pos = (pos + 1) % positions.size();
		return ret;
	}

private:
	std::vector<Vectorf> positions;
	int pos;
};
