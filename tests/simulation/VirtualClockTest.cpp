#include <gtest/gtest.h>

#include "simulation/VirtualClock.h"

TEST(VirtualClockTest, StartsAtZero)
{
    VirtualClock clock;

    EXPECT_DOUBLE_EQ(clock.getCurrentTime(), 0.0);
}

TEST(VirtualClockTest, AdvancesTimeCorrectly)
{
    VirtualClock clock;

    clock.advanceTime(5.0);

    EXPECT_DOUBLE_EQ(clock.getCurrentTime(), 5.0);
}

TEST(VirtualClockTest, AccumulatesMultipleTimeAdvances)
{
    VirtualClock clock;

    clock.advanceTime(2.0);
    clock.advanceTime(3.0);
    clock.advanceTime(5.0);

    EXPECT_DOUBLE_EQ(clock.getCurrentTime(), 10.0);
}

TEST(VirtualClockTest, IgnoresNegativeTimeAdvance)
{
    VirtualClock clock;

    clock.advanceTime(5.0);
    clock.advanceTime(-2.0);

    EXPECT_DOUBLE_EQ(clock.getCurrentTime(), 5.0);
}

TEST(VirtualClockTest, ResetSetsTimeToZero)
{
    VirtualClock clock;

    clock.advanceTime(10.0);
    clock.reset();

    EXPECT_DOUBLE_EQ(clock.getCurrentTime(), 0.0);
}