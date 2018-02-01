#include <algorithm>

template<typename T>
struct Vector {
	T x;
	T y;
};

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
int lastPos = 0;
Vector<int> lastValuesSorted[lastCount];
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
		int rx, ry;
		touch.read(rx, ry, pressure);
		//if(pressure > 120000 || rx > 65000 || ry > 65000) {
		//	return false;
		//}

		lastValues[lastPos].x = rx;
		lastValues[lastPos].y = ry;
		lastPos = (lastPos + 1) % lastCount;

		for(int i = 0; i < lastCount; i++) {
			lastValuesSorted[i] = lastValues[i];
		}
		std::sort(lastValuesSorted, lastValuesSorted + lastCount, comparator);




		const int maxDiff = 3000;
		Vector<int> &median = lastValuesSorted[lastCount / 2];
		if(abs(rx - median.x) > maxDiff || abs(ry - median.y) > maxDiff) {
			return false;
		}


		RX = rx;
		RY = ry;

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

	Vector<int> lastValues[lastCount];

	double map(int val, int min, int max) {
		return ((double) val - min) / (max - min) * 2 - 1;
	}
};
