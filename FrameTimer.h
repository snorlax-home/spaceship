#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class FrameTimer
{
private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrev;
	int requestedFps;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;

public:
	void Init(int);
	int FramesToUpdate();

};