#include <mbed.h>
#include <mbed_events.h>
#include "Touch.h"
#include "TouchPanel.h"
#include "config.h"
#include "commands.h"
#include "demo.h"

#define us2dc(t, us) ((double) (us) / ((t)*1000))

Configuration conf;

Serial pc(USBTX, USBRX);
Touch touch(MBED_CONF_APP_PIN_XP, MBED_CONF_APP_PIN_XM, MBED_CONF_APP_PIN_YP, MBED_CONF_APP_PIN_YM);
Filter filter(&touch);
TouchPanel panel(&filter);
VelocityTracker tracker(&filter);
PwmOut servoX(MBED_CONF_APP_PIN_SERVOX), servoY(MBED_CONF_APP_PIN_SERVOY);
InterruptIn centerBtn(MBED_CONF_APP_PIN_BTN_CENTER);
InterruptIn rectBtn(MBED_CONF_APP_PIN_BTN_DEMO);

#if INPUT_METHOD == INPUT_METHOD_TOUCH
	TouchPanel &input = panel;
#elif INPUT_METHOD == INPUT_METHOD_ACCELEROMETER
	#include "Accelerometer.h"
	AccelerometerInput input;
#else
	#error "wrong input method"
#endif

int i = 0;
Vector<double> planeNormal;

double cap(double val) {
	return std::min(std::max(val, SHIFT_MIN_US), SHIFT_MAX_US);
}

void control() {
	double x, y, z = 1;

	tracker.update();

	if(conf.state == STATE_BALANCE) {
		planeNormal = planeNormal - (conf.const_p * tracker.getSpeed() + conf.const_k * tracker.getAcceleration());
		planeNormal = normalize(planeNormal);

		x = planeNormal.x;
		y = planeNormal.y;
	} else if(conf.state == STATE_DEMO && !conf.positions.empty()) {
		Vectorf v = conf.positions.current();

		x = v.x;
		y = v.y;

		if(i % 50 == 0) {
			conf.positions.next();
		}
	} else {
		return;
	}

	double zx = -x * MX / z;
	double zy = -y * MY / z;

	double angleX = zx / MX;
	double angleY = zy / MY;

	double DX = angleX * 1800 / M_PI;
	double DY = angleY * 1800 / M_PI;

	double USX = us2dc(DUTY_MS, CENTER_X_US + cap(DX));
	double USY = us2dc(DUTY_MS, CENTER_Y_US + cap(DY));

	pc.printf("RX=%d RY=%d USX=%1.4f USY=%1.4f vx=%1.4f vy=%1.4f ax=%1.4f ay=%1.4f\r\n",
			tracker.getResistance().x, tracker.getResistance().y,
			USX, USY,
			tracker.getSpeed().x, tracker.getSpeed().y,
			tracker.getAcceleration().x, tracker.getAcceleration().y
	);

	if(conf.enabledServos) {
		servoX.write(USX);
		servoY.write(USY);
	}

	i++;
}

void center() {
	servoX.write(us2dc(DUTY_MS, CENTER_X_US));
	servoY.write(us2dc(DUTY_MS, CENTER_Y_US));
	conf.state = STATE_STOP;
}

void rect() {
	conf.state = STATE_DEMO;
	conf.positions.reset();
}


int main() {
	pc.baud(115200);
	pc.printf("Initialized\n");

	CommandsProcessor cmds(pc, conf);
	cmds.start();

	centerBtn.fall(&center);
	rectBtn.fall(&rect);

	servoX.period(DUTY_MS / 1000.0);
	servoY.period(DUTY_MS / 1000.0);

	panel.setPressureThreshold(120000);
	panel.calibrateX(8800, 49600, true);
	panel.calibrateY(13000, 42568, true);
	panel.setSwapXY(true);
	panel.setSwapXY(true);

	EventQueue queue;
	queue.call_every(MEASUREMENT_PERIOD_MS, control);
	queue.dispatch();
}
