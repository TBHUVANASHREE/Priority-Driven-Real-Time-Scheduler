#include <gtest/gtest.h>

#include <memory>

#include "scheduler/RMSPolicy.h"
#include "task/SensorTask.h"
#include "task/ControlTask.h"
#include "task/SafetyTask.h"

TEST(RMSPolicyTest, ShorterPeriodHasHigherPriority)
{
    RMSPolicy policy;

    auto fastTask = std::make_shared<SafetyTask>(
        1,
        "Airbag Monitoring",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        10.0,
        2.0
    );

    auto slowTask = std::make_shared<SensorTask>(
        2,
        "Engine Temperature",
        SafetyLevel::MEDIUM,
        5,
        0.0,
        100.0,
        3.0
    );

    EXPECT_TRUE(
        policy.higherPriority(fastTask, slowTask)
    );
}

TEST(RMSPolicyTest, LongerPeriodHasLowerPriority)
{
    RMSPolicy policy;

    auto fastTask = std::make_shared<ControlTask>(
        1,
        "Brake Control",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        20.0,
        2.0
    );

    auto slowTask = std::make_shared<SensorTask>(
        2,
        "Battery Monitoring",
        SafetyLevel::MEDIUM,
        4,
        0.0,
        100.0,
        5.0
    );

    EXPECT_FALSE(
        policy.higherPriority(slowTask, fastTask)
    );
}

TEST(RMSPolicyTest, EqualPeriodsDoNotHaveHigherPriority)
{
    RMSPolicy policy;

    auto firstTask = std::make_shared<SensorTask>(
        1,
        "Wheel Speed",
        SafetyLevel::HIGH,
        2,
        0.0,
        20.0,
        2.0
    );

    auto secondTask = std::make_shared<ControlTask>(
        2,
        "Steering Control",
        SafetyLevel::HIGH,
        3,
        0.0,
        20.0,
        4.0
    );

    EXPECT_FALSE(
        policy.higherPriority(firstTask, secondTask)
    );
}

TEST(RMSPolicyTest, NullTaskIsHandledSafely)
{
    RMSPolicy policy;

    auto task = std::make_shared<SensorTask>(
        1,
        "Wheel Speed",
        SafetyLevel::HIGH,
        2,
        0.0,
        20.0,
        2.0
    );

    EXPECT_FALSE(
        policy.higherPriority(nullptr, task)
    );

    EXPECT_TRUE(
        policy.higherPriority(task, nullptr)
    );
}