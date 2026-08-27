#include "simulation/VirtualClock.h"

VirtualClock::VirtualClock()
    : currentTime(0.0)
{
}

void VirtualClock::reset()
{
    currentTime = 0.0;
}

void VirtualClock::advanceTime(double deltaTime)
{
    if (deltaTime > 0.0)
    {
        currentTime += deltaTime;
    }
}

double VirtualClock::getCurrentTime() const
{
    return currentTime;
}