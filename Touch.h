#pragma once
#include "mbed.h"
#include <algorithm>

#define MEASURES 16


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

		int sum = 0;
		for(int i = MEASURES / 4; i < 3 * MEASURES / 4; i++) {
			sum += measures[i];
		}

		return sum / (MEASURES / 2);
	}

	int readY() {
		DigitalOut xp(pinXP), xm(pinXM);
		AnalogIn yp(pinYP), ym(pinYM);

		xp = true;
		xm = false;

		return measure(ym);
	}

	int readX() {
		DigitalOut yp(pinYP), ym(pinYM);
		AnalogIn xp(pinXP), xm(pinXM);

		yp = true;
		ym = false;

		return measure(xm);
	}

	int readPressure() {
		DigitalOut xp(pinXP), ym(pinYM);
		AnalogIn xm(pinXM), yp(pinYP);

		xp = false;
		ym = true;

		return 65535 - (xm.read_u16() - yp.read_u16());
	}
};

class Panel {
public:
	Panel(Touch &touch): touch(touch) {}

	bool getPos(double &X, double &Y) {
		int RX, RY, pressure;
		return getPosRaw(X, Y, RX, RY, pressure);
	}

	bool getPosRaw(double &X, double &Y, int &RX, int &RY, int &pressure) {
		touch.read(RX, RY, pressure);

		X = map(RX, minX, maxX);
		/*if(reverseX) {
		    X = width - X;
		}*/

		Y = map(RY, minY, maxY);
		/*if(reverseY) {
		    Y = height - Y;
		}*/

		std::swap(X, Y);

		return pressure < thresholdPressure;
	}

	void setPressureThreshold(int pressure) {
		thresholdPressure = pressure;
	}

	void calibrateX(int min, int max, bool reverse) {
		minX = min;
		maxX = max;
		reverseX = reverse;
	}

	void calibrateY(int min, int max, bool reverse) {
		minY = min;
		maxY = max;
		reverseY = reverse;
	}

private:
	Touch &touch;
	int thresholdPressure;
	int minX, maxX;
	int minY, maxY;
	bool reverseX, reverseY;

	double map(int val, int min, int max) {
		return ((double) val - min) / (max - min) * 2 - 1;
	}
};
