#include "mbed.h"
#include "Touch.h"

const PinName PIN_YM = A0;
const PinName PIN_XM = A1;
const PinName PIN_YP = A2;
const PinName PIN_XP = A3;

Serial pc(USBTX, USBRX);
Touch touch(PIN_XP, PIN_XM, PIN_YP, PIN_YM);
Panel panel(touch, 180, 230);

int main() {
	pc.baud(115200);
    pc.printf("Hello World!\r\n");

	panel.setPressureThreshold(100000);
	panel.calibrateX(12200, 40700, true);
	panel.calibrateY(8600, 48900, true);

	int X, Y, RX, RY, pressure;
	bool pressed;
    while (true) {
		pressed = panel.getPosRaw(X, Y, RX, RY, pressure);
		pc.printf("X=%d Y=%d RX=%d RY=%d pressure=%d pressed=%d\r\n", X, Y, RX, RY, pressure, pressed);
		wait(0.05f);
    }
}
