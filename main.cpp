#include "mbed.h"
#include "FXOS8700Q.h"
#include "Touch.h"

const PinName PIN_YM = A0;
const PinName PIN_XM = A1;
const PinName PIN_YP = A2;
const PinName PIN_XP = A3;

Serial pc(USBTX, USBRX);
Touch touch(PIN_XP, PIN_XM, PIN_YP, PIN_YM);
Panel panel(touch, 180, 230);

PwmOut servoX(PTC10), servoY(PTC11);

FXOS8700Q_acc acc( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);

double cap(double val) {
	return min(max(val, -0.012), 0.012);
}

int main() {
	pc.baud(115200);
	pc.printf("Hello World!\r\n");

	servoX.period(0.020);
	servoY.period(0.020);


	MotionSensorDataUnits acc_data;
	acc.enable();


	int MX = 90, MY = 90;
	int PX = 30, PY = 30;

	double val = 0.065;
	double add = 0.001;

	double centerX = 0.080;
	double centerY = 0.075;


/*	servoX.write(0.080);
	servoY.write(0.075);

	for(;;);

	for(;;) {
		for(int i = 0; i < 20; i++) {
			val += add;
	//		servoX.write(val);
	//		servoY.write(val);
			wait(0.05f);
			pc.printf("%1.4f\r\n", val);
		}
		add *= -1;
	}

	servoX.write(0.065f);
	*/
	double DX, DY;
	for(;;) {
		acc.getAxis(acc_data);
		float normalized = sqrt(acc_data.x * acc_data.x + acc_data.y * acc_data.y + acc_data.z * acc_data.z);

		float x = acc_data.x / normalized;
		float y = acc_data.y / normalized;
		float z = acc_data.z / normalized;

		float zx = -x * MX / z;
		float zy = -y * MY / z;


		float angleX = zx / MX;
		float angleY = zy / MY;

		#define us2dc(t, us) ((double) (us) / ((t)*1000))
		double USX, USY;

//		USX = cap(angleX * 1800 / 3.14 * 0.00005);
//		USY = cap(angleY * 1800 / 3.14 * 0.00005);


		double DX = angleX * 1800 / 3.14;
		double DY = angleY * 1800 / 3.14;
		
		USX = us2dc(20, 1600) + cap(us2dc(20, DX));
		USY = us2dc(20, 1500) + cap(us2dc(20, DY));

		printf("FXOS8700Q ACC: X=%1.4f Y=%1.4f Z=%1.4f normalized: %1.4f DX=%f DY=%f\r\n", x, y, z, normalized, USX, USY);
		servoX.write(USX);
		servoY.write(USY);
		wait(0.05f);
	}

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
