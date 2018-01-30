#include <mbed.h>
#include <mbed_events.h>
#include "Accelerometer.h"
#include "Touch.h"
#include "config.h"

#define us2dc(t, us) ((double) (us) / ((t)*1000))

Serial pc(USBTX, USBRX);
Touch touch(PIN_XP, PIN_XM, PIN_YP, PIN_YM);
TouchPanel panel(touch);
PwmOut servoX(PTC10), servoY(PTC11);

DigitalOut led1(LED1);

typedef struct {
	float x;
	float y;
} Point;

const int pointCount = 10;
int lastPoint = 0;
Point lastPoints[pointCount];

#if INPUT_METHOD == INPUT_METHOD_TOUCH
	TouchPanel &input = panel;
#elif INPUT_METHOD == INPUT_METHOD_ACCELEROMETER
	AccelerometerInput input;
#else
	#error "wrong input method"
#endif

Point normalize(const Point &point) {
	double normalized = sqrt(point.x * point.x + point.y * point.y);
	Point p;
	p.x = point.x / normalized;
	p.y = point.y / normalized;
	return p;
}

double cap(double val) {
	return std::min(std::max(val, SHIFT_MIN_US), SHIFT_MAX_US);
}

void control() {
	double x, y, z = 1;

	if(!input.getPos(x, y)) {
		led1 = false;
		servoX.write(0);
		servoY.write(0);
		return;
	}
	led1 = true;

	lastPoints[lastPoint].x = x;
	lastPoints[lastPoint].y = y;
	lastPoint = lastPoint % pointCount;

	Point dir;
	for(int i = 0; i < pointCount; i++) {
		dir.x += lastPoints[i].x;
		dir.y += lastPoints[i].y;
	}
	dir = normalize(dir);
	x = dir.x;
	y = dir.y;

	double zx = -x * MX / z;
	double zy = -y * MY / z;

	double angleX = zx / MX;
	double angleY = zy / MY;

	double DX = angleX * 1800 / M_PI;
	double DY = angleY * 1800 / M_PI;

	double USX = us2dc(DUTY_MS, CENTER_X_US + cap(DX));
	double USY = us2dc(DUTY_MS, CENTER_Y_US + cap(DY));

	printf("FXOS8700Q ACC: X=%1.4f Y=%1.4f Z=%1.4f DX=%f DY=%f\r\n", x, y, z, USX, USY);
	servoX.write(USX);
	servoY.write(USY);
}


int main() {
 	led1 = true;

	pc.baud(115200);
	pc.printf("Hello World!\r\n");

	servoX.period(DUTY_MS / 1000.0);
	servoY.period(DUTY_MS / 1000.0);

#ifdef FUNCTION_CENTER
	servoX.write(us2dc(DUTY_MS, CENTER_X_US));
	servoY.write(us2dc(DUTY_MS, CENTER_Y_US));
	for(;;);
#endif

	panel.setPressureThreshold(100000);
	panel.calibrateX(12200, 40700, true);
	panel.calibrateY(8600, 48900, true);
	panel.setSwapXY(true);

#ifdef FUNCTION_CALIBRATE
	double X, Y;
	int RX, RY, pressure;
	bool pressed;
	while (true) {
		pressed = panel.getPosRaw(X, Y, RX, RY, pressure);
		pc.printf("X=0 Y=0 RX=%d RY=%d pressure=%d pressed=%d\r\n", RX, RY, pressure, pressed);
		wait(0.02f);
	}
#endif

	EventQueue queue;

	queue.call_every(MEASUREMENT_PERIOD_MS, control);
	queue.dispatch();
}
