#include <algorithm>
#include "Utils.h"

class Filter: public ITouch {
public:
	Filter(ITouch *touch): fails(0), touch(touch) {}

	void read(int &RX, int &RY, int &pressure) {
		touch->read(RX, RY, pressure);

		const int threshold = 60000;
		const int threshold2 = 1000;
		const int max_set = 65000;

		if(RX > threshold || RX < threshold2) {
			RX = prevPos.x + prevSpeed.x;
			fails++;

			if(fails > 20) {
				RX = max_set;
			}
		} else {
			fails = 0;
		}
		prevSpeed.x = RX - prevPos.x;


		if(RY > threshold || RY < threshold2) {
			RY = prevPos.y + prevSpeed.y;
			fails++;

			if(fails > 20) {
				RY = max_set;
			}
		} else {
			fails = 0;
		}
		prevSpeed.y = RY - prevPos.y;
	}

private:
	Vector<int> prevPos;
	Vector<int> prevSpeed;
	int fails;
	ITouch *touch;
};

class TouchPanel {
public:
	TouchPanel(ITouch *touch):
			touch(touch),
			reverseX(false),
			reverseY(false),
			swapXY(false){}

	bool getPos(double &X, double &Y) {
		int RX, RY, pressure;
		return getPosRaw(X, Y, RX, RY, pressure);
	}

	bool getPosRaw(double &X, double &Y, int &RX, int &RY, int &pressure) {
		touch->read(RX, RY, pressure);

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
	ITouch *touch;
	int thresholdPressure;
	int minX, maxX;
	int minY, maxY;
	bool reverseX, reverseY;
	bool swapXY;

	double map(int val, int min, int max) {
		return ((double) val - min) / (max - min) * 2 - 1;
	}
};

class VelocityTracker {
public:
	VelocityTracker(ITouch *touch): touch(touch) {}
	void update() {
		int RX, RY, pressure;
		touch->read(RX, RY, pressure);

		prevResistance = curResistance;
		curResistance.x = RX;
		curResistance.y = RY;

		prevSpeed = curSpeed;
		curSpeed.x = curResistance.x - prevResistance.x;
		curSpeed.y = curResistance.y - prevResistance.y;

		acceleration.x = curSpeed.x - prevSpeed.x;
		acceleration.y = curSpeed.y - prevSpeed.y;
	}

	const Vector<int>& getResistance() const {
		return curResistance;
	}

	const Vector<double>& getSpeed() const {
		return curSpeed;
	}

	const Vector<double>& getAcceleration() const {
		return curSpeed;
	}

private:
	ITouch *touch;
	Vector<int> prevResistance, curResistance;
	Vector<double> prevSpeed, curSpeed;
	Vector<double> acceleration;
};
