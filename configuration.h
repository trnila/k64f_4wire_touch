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
	double USX, USY;

	Configuration() {
		state = STATE_BALANCE;
		enabledServos = true;
		const_k = 0.0005;
		const_p = 0;
	}
};
