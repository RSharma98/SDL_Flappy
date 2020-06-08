#ifndef MATHHELPER_H
#define MATHHELPER_H

class MathHelper {
public:
	static int Sign(float val) { return val >= 0 ? 1 : -1; }
	static float Clamp(float value, float min, float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	static float Lerp(float start, float target, float t) {
		t = Clamp(t, 0, 1);
		return start + ((target - start) * t);
	}
};
#endif // !MATHHELPER_H
