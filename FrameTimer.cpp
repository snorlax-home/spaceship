#include "FrameTimer.h"
#include <iostream>

void FrameTimer::Init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrev);

	requestedFps = fps;

	intervalsPerFrame = ((float)timerFreq.QuadPart / requestedFps);

}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);
	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrev.QuadPart;

	framesToUpdate = (int)(intervalsSinceLastUpdate /
		intervalsPerFrame);
	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&timePrev);
	}
	return framesToUpdate;
}