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

	Configuration() {
		state = STATE_BALANCE;
	}
};
