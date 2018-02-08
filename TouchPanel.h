#include <algorithm>
#include "Utils.h"

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
	Touch &touch;
	int thresholdPressure;
	int minX, maxX;
	int minY, maxY;
	bool reverseX, reverseY;
	bool swapXY;

	double map(int val, int min, int max) {
		return ((double) val - min) / (max - min) * 2 - 1;
	}
};
