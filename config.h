#pragma once

#define INPUT_METHOD_TOUCH 0
#define INPUT_METHOD_ACCELEROMETER 1

//#define FUNCTION_CENTER 100
//#define FUNCTION_CALIBRATE 101


// configurable
#define INPUT_METHOD INPUT_METHOD_TOUCH

const int MX = 90, MY = 90;
const int PX = 30, PY = 30;
const int DUTY_MS = 20;
const int CENTER_X_US = 1600;
const int CENTER_Y_US = 1575;
const double SHIFT_MIN_US = -100;
const double SHIFT_MAX_US = 100;
const double SHIFT_MM = 12;

const int MEASUREMENT_PERIOD_MS = DUTY_MS;

const int MAX_CMD_ARGS = 6;
