#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class Touch {
public:
	Touch(FILE* fd): fd(fd) {}

	void read(int &RX, int &RY, int &pressure) {
		usleep(20000);
		if(fscanf(fd, "%d %d %d", &RX, &RY, &pressure) != 3) {
			exit(0);
		}
	}

private:
	FILE* fd;
};

#include "TouchPanel.h"

struct Vector {
	double x;
	double y;
};

int main() {
	Touch touch(stdin);
	TouchPanel panel(touch);


	Vector prev

	double X, Y;
	int RX, RY, pressure;
	bool pressed;
	while (true) {
		pressed = panel.getPosRaw(X, Y, RX, RY, pressure);
		printf("X=0 Y=0 RX=%d RY=%d pressure=%d pressed=%d\r\n", RX, RY, pressure, pressed);
		fflush(stdout);
	}
}