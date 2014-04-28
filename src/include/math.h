#ifndef UGINE_MATH_H
#define UGINE_MATH_H

#include <math.h>
#include <stdlib.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

template <typename T> T Min(T a, T b) {
	return (a < b) ? a : b;
}

template <typename T> T Max(T a, T b) {
	return (a > b) ? a : b;
}

inline double Log2(double x) {
	return log(x) / log(2.0);
}

inline double Log10(double x) {
	return log(x) / log(10.0);
}

inline double DegSin(double degrees) {
	return sin(DEG2RAD * degrees);
}

inline double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

inline double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

inline double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

inline double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

inline double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

inline double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

inline int Rand(int min, int max) {
	return min + (rand() % (max - min));
}

inline double Rand(double min, double max) {
	return min + (rand() % (int)(max*1000 - min*1000))/1000.0f;
}

inline double Wrap(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val/mod);
}

inline double Interpolate(double id, double prevId, double nextId, double prevVal, double nextVal) {
	return prevVal + (nextVal - prevVal) * ((id - prevId) / (nextId - prevId));
}

#undef DEG2RAD
#undef RAD2DEG

#endif // UGINE_MATH_H
