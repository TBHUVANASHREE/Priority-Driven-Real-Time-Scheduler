#pragma once

class VirtualClock
{
private:
    double currentTime;

public:
    VirtualClock();

    void reset();

    void advanceTime(double deltaTime);

    double getCurrentTime() const;
};