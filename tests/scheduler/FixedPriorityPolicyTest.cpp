#include <gtest/gtest.h>

#include <memory>

#include "scheduler/FixedPriorityPolicy.h"
#include "task/SensorTask.h"
#include "task/ControlTask.h"
#include "task/SafetyTask.h"

TEST(FixedPriorityPolicyTest, HigherPriorityTaskIsSelected)
{
    FixedPriorityPolicy policy;

    auto safetyTask = std::make_shared<SafetyTask>(
        1,
        "Airbag Monitoring",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        50.0,
        3.0
    );

    auto sensorTask = std::make_shared<SensorTask>(
        2,
        "Wheel Speed Monitoring",
        SafetyLevel::HIGH,
        3,
        0.0,
        20.0,
        2.0
    );

    EXPECT_TRUE(
        policy.higherPriority(safetyTask, sensorTask)
    );
}

TEST(FixedPriorityPolicyTest, LowerPriorityTaskIsNotSelected)
{
    FixedPriorityPolicy policy;

    auto safetyTask = std::make_shared<SafetyTask>(
        1,
        "Airbag Monitoring",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        50.0,
        3.0
    );

    auto sensorTask = std::make_shared<SensorTask>(
        2,
        "Wheel Speed Monitoring",
        SafetyLevel::HIGH,
        3,
        0.0,
        20.0,
        2.0
    );

    EXPECT_FALSE(
        policy.higherPriority(sensorTask, safetyTask)
    );
}

TEST(FixedPriorityPolicyTest, EqualPriorityDoesNotHaveHigherPriority)
{
    FixedPriorityPolicy policy;

    auto firstTask = std::make_shared<ControlTask>(
        1,
        "Brake Control",
        SafetyLevel::CRITICAL,
        2,
        0.0,
        20.0,
        5.0
    );

    auto secondTask = std::make_shared<SensorTask>(
        2,
        "Wheel Speed Monitoring",
        SafetyLevel::HIGH,
        2,
        0.0,
        20.0,
        2.0
    );

    EXPECT_FALSE(
        policy.higherPriority(firstTask, secondTask)
    );
}

TEST(FixedPriorityPolicyTest, NullTaskIsHandledSafely)
{
    FixedPriorityPolicy policy;

    auto task = std::make_shared<SensorTask>(
        1,
        "Battery Monitoring",
        SafetyLevel::MEDIUM,
        3,
        0.0,
        100.0,
        4.0
    );

    EXPECT_FALSE(
        policy.higherPriority(nullptr, task)
    );

    EXPECT_TRUE(
        policy.higherPriority(task, nullptr)
    );
}