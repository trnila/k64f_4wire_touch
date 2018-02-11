#pragma once
#include "demo.h"

enum State {
	STATE_STOP,
	STATE_BALANCE,
	STATE_DEMO
};

struct Configuration {
	State state;
	DemoPositions positions;
	double const_k, const_p;
	bool enabledServos;

	Configuration() {
		state = STATE_BALANCE;
		enabledServos = false;
		const_k = 0;
		const_p = 0;
	}
};
