#pragma once
#include <mbed.h>
#include <FXOS8700Q.h>

class AccelerometerInput {
public:
	AccelerometerInput(): acc(PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1) {
		acc.enable();
	}

	bool getPos(double &X, double &Y) {
		MotionSensorDataUnits acc_data;
		acc.getAxis(acc_data);

		double normalized = sqrt(acc_data.x * acc_data.x + acc_data.y * acc_data.y + acc_data.z * acc_data.z);
		X = acc_data.x / normalized;
		Y = acc_data.y / normalized;

		return true;
	}

private:
	FXOS8700Q_acc acc;
};
