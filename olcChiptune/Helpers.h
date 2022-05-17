#pragma once

namespace Math {

	template <class T>
	T clamp(T value, T min, T max) {
		if(value > max) return max;
		if(value < min) return min;
		return value;
	}
}