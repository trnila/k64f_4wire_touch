#include <mbed.h>
#include "Accelerometer.h"
#include "Touch.h"


#define INPUT_METHOD_TOUCH 0
#define INPUT_METHOD_ACCELEROMETER 1

#define INPUT_METHOD INPUT_METHOD_ACCELEROMETER

const PinName PIN_YM = A0;
const PinName PIN_XM = A1;
const PinName PIN_YP = A2;
const PinName PIN_XP = A3;

Serial pc(USBTX, USBRX);
Touch touch(PIN_XP, PIN_XM, PIN_YP, PIN_YM);
TouchPanel panel(touch);

PwmOut servoX(PTC10), servoY(PTC11);

const int MX = 90, MY = 90;
const int PX = 30, PY = 30;
const int DUTY_MS = 20;
const int CENTER_X_US = 1600;
const int CENTER_Y_US = 1500;
const double SHIFT_MIN = -0.012; //- 250
const double SHIFT_MAX = 0.012; // 250

#define us2dc(t, us) ((double) (us) / ((t)*1000))


double cap(double val) {
	return min(max(val, SHIFT_MIN), SHIFT_MAX);
}


int main() {
	pc.baud(115200);
	pc.printf("Hello World!\r\n");

	servoX.period(DUTY_MS / 1000.0);
	servoY.period(DUTY_MS / 1000.0);

	panel.setPressureThreshold(100000);
	panel.calibrateX(12200, 40700, true);
	panel.calibrateY(8600, 48900, true);


#if INPUT_METHOD == INPUT_METHOD_TOUCH
	TouchPanel &input = panel;
#elif INPUT_METHOD == INPUT_METHOD_ACCELEROMETER
	AccelerometerInput input;
#else
	#error "wrong input method"
#endif

	for(;;) {
		double x, y, z = 1;

		if(!input.getPos(x, y)) {
			servoX.write(0);
			servoY.write(0);
			continue;
		}

		double zx = -x * MX / z;
		double zy = -y * MY / z;

		double angleX = zx / MX;
		double angleY = zy / MY;

		double DX = angleX * 1800 / M_PI;
		double DY = angleY * 1800 / M_PI;

		double USX = us2dc(DUTY_MS, CENTER_X_US) + cap(us2dc(DUTY_MS, DX));
		double USY = us2dc(DUTY_MS, CENTER_Y_US) + cap(us2dc(DUTY_MS, DY));

		printf("FXOS8700Q ACC: X=%1.4f Y=%1.4f Z=%1.4f DX=%f DY=%f\r\n", x, y, z, USX, USY);
		servoX.write(USX);
		servoY.write(USY);
		wait(0.05f);
	}
}
