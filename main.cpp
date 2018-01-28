#include "mbed.h"
#include "Touch.h"

const PinName PIN_YM = A0;
const PinName PIN_XM = A1;
const PinName PIN_YP = A2;
const PinName PIN_XP = A3;

Serial pc(USBTX, USBRX);
Touch touch(PIN_XP, PIN_XM, PIN_YP, PIN_YM);
Panel panel(touch);


int main() {
	pc.baud(115200);
    pc.printf("Hello World!\r\n");

	int X, Y, pressure;
    while (true) {
		panel.getPos(X, Y);
		pc.printf("X=%d Y=%d pressure=%d\r\n", X, Y, pressure);
		wait(0.05f);
    }
}
