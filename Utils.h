#pragma once

template<typename T>
struct Vector {
	T x;
	T y;

	Vector(T x, T y): x(x), y(y) {}
	Vector(): x(0), y(0) {}
};

typedef Vector<double> Vectorf;
typedef Vector<int> Vectori;

template<typename T>
bool vectorComparator(const Vector<T> &a, const Vector<T> &b) {
	if(a.x < b.x) {
		return true;
	}

	if(a.x == b.x) {
		return a.y < b.y;
	}

	return false;
}

template<typename T>
Vector<T> normalize(const Vector<T> &point) {
	double normalized = sqrt(point.x * point.x + point.y * point.y);
	Vector<T> p;
	p.x = point.x / normalized;
	p.y = point.y / normalized;
	return p;
}
