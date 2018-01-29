#pragma once

#define INPUT_METHOD_TOUCH 0
#define INPUT_METHOD_ACCELEROMETER 1

// configurable
#define INPUT_METHOD INPUT_METHOD_ACCELEROMETER

const PinName PIN_YM = A0;
const PinName PIN_XM = A1;
const PinName PIN_YP = A2;
const PinName PIN_XP = A3;

const int MX = 90, MY = 90;
const int PX = 30, PY = 30;
const int DUTY_MS = 20;
const int CENTER_X_US = 1600;
const int CENTER_Y_US = 1500;
const double SHIFT_MIN_US = -250;
const double SHIFT_MAX_US = 250;
