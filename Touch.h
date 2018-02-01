#pragma once
#include "mbed.h"
#include <algorithm>

#define MEASURES 10

class Touch {
public:
	Touch(PinName pinXP, PinName pinXM, PinName pinYP, PinName pinYM):
		pinXP(pinXP),
		pinXM(pinXM),
		pinYP(pinYP),
		pinYM(pinYM) {}

	void read(int &X, int &Y, int &pressure) {
		Y = readY();
		X = readX();
		pressure = readPressure();
	}

private:
	PinName pinXP, pinXM;
	PinName pinYP, pinYM;

	uint16_t measure(AnalogIn in) {
		uint16_t measures[MEASURES];

		for(int i = 0; i < MEASURES; i++) {
			measures[i] = in.read_u16();
		}

		std::sort(measures, measures + MEASURES);

		//int sum = 0;
	//	for(int i = MEASURES / 4; i < 3 * MEASURES / 4; i++) {
//			sum += measures[i];
		//}

		//return sum / (MEASURES / 2);
		return measures[MEASURES / 2];
	}

	int readY() {
		int value;
		{
			DigitalOut xp(pinXP, true), xm(pinXM, false);
			AnalogIn yp(pinYP), ym(pinYM);
			wait_us(100);

			value = measure(ym);
		}

		{
			DigitalOut xp(pinXP), xm(pinXM);
			xp = xm = 1;
			wait_us(100);
		}

		return value;
	}

	int readX() {
		int value;
		{
			DigitalOut yp(pinYP, true), ym(pinYM, false);
			AnalogIn xp(pinXP), xm(pinXM);
			wait_us(100);

			value = measure(xm);
		}

		{
			DigitalOut yp(pinYP), ym(pinYM);
			yp = ym = 1;
			wait_us(100);
		}

		return value;
	}

	int readPressure() {
		DigitalOut xp(pinXP, false), ym(pinYM, true);
		AnalogIn xm(pinXM), yp(pinYP);
		return 65535 - (xm.read_u16() - yp.read_u16());
	}
};
