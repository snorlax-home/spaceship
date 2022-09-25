 #pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/**
 * \brief Frame Timer class to let the game to be run at a fixed FPS
 */
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
    /**
     * \brief Initializes the frame timer
     * \param fps the cap of the FPS
     */
    void Init(int fps);
    /**
     * \brief Get the number of frames to update
     * \return The number of frames to update
     */
    int FramesToUpdate();
};
