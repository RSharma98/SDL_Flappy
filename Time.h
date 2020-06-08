#ifndef TIME_H
#define TIME_H

class Time {
public:
	static double GetDeltaTime() { return deltaTime; }
	static double GetTotalTime() { return totalTime; }
	static void SetDeltaTime(double dt) { deltaTime = dt; totalTime += dt; }

private:
	static double deltaTime;	//The difference in time between frames
	static double totalTime;	//The total time since the game began
};
#endif // !TIME_H