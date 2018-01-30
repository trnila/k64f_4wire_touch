#pragma once
#include "mbed.h"
#include <algorithm>

#define MEASURES 16

template<typename T>
struct Vector {
	T x;
	T y;
};

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
		pressure = 90000;
		//pressure = readPressure();
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
		int value;
		{
			DigitalOut xp(pinXP), xm(pinXM);
			AnalogIn yp(pinYP), ym(pinYM);

			xp = true;
			xm = false;

			value = measure(ym);
		}

		{
			DigitalIn xp(pinXP), xm(pinXM);
			wait_us(100);
		}

		return value;
	}

	int readX() {
		int value;
		{
			DigitalOut yp(pinYP), ym(pinYM);
			AnalogIn xp(pinXP), xm(pinXM);

			yp = true;
			ym = false;

			value = measure(xm);
		}

		{
			DigitalIn yp(pinYP), ym(pinYM);
			wait_us(100);
		}

		return value;
	}

	int readPressure() {
		DigitalOut xp(pinXP), ym(pinYM);
		AnalogIn xm(pinXM), yp(pinYP);

		xp = false;
		ym = true;

		return 65535 - (xm.read_u16() - yp.read_u16());
	}
};

bool xComparator(const Vector<int> &a, const Vector<int> &b) {
	return a.x < b.x;
}

bool comparator(const Vector<int> &a, const Vector<int> &b) {
	if(a.x < b.x) {
		return true;
	}

	if(a.x == b.x) {
		return a.y < b.y;
	}

	return false;
}

const int lastCount = 20;
class TouchPanel {
public:
	TouchPanel(Touch &touch):
		touch(touch),
		reverseX(false),
		reverseY(false),
		swapXY(false){}

	bool getPos(double &X, double &Y) {
		int RX, RY, pressure;
		return getPosRaw(X, Y, RX, RY, pressure);
	}

	bool getPosRaw(double &X, double &Y, int &RX, int &RY, int &pressure) {
		touch.read(RX, RY, pressure);
		lastValues[lastPos].x = RX;
		lastValues[lastPos].y = RY;
		lastPos = (lastPos + 1) % lastCount;

		std::stable_sort(lastValues, lastValues + lastCount, comparator);

		RX = 0;
		RY = 0;
		for(int i = lastCount / 4; i < 3 * lastCount / 4; i++) {
			RX += lastValues[i].x;
			RY += lastValues[i].y;
		}
		RX /= lastCount / 2;
		RY /= lastCount / 2;

		X = map(RX, minX, maxX);
		if(reverseX) {
		    X *= -1;
		}

		Y = map(RY, minY, maxY);
		if(reverseY) {
		    Y *= -1;
		}

		if(swapXY) {
			std::swap(X, Y);
		}

		return true;
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

	void setSwapXY(bool swap = true) {
		swapXY = swap;
	}

private:
	Touch &touch;
	int thresholdPressure;
	int minX, maxX;
	int minY, maxY;
	bool reverseX, reverseY;
	bool swapXY;

	int lastPos = 0;
	Vector<int> lastValues[lastCount];

	double map(int val, int min, int max) {
		return ((double) val - min) / (max - min) * 2 - 1;
	}
};
