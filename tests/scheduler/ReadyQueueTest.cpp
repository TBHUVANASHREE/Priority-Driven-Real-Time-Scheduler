#include <gtest/gtest.h>

#include <memory>

#include "scheduler/ReadyQueue.h"
#include "task/SensorTask.h"

class TestPriorityPolicy : public SchedulingPolicy
{
public:
    bool higherPriority(
        const std::shared_ptr<Task>& first,
        const std::shared_ptr<Task>& second
    ) const override
    {
        return first->getPriority() < second->getPriority();
    }
};

TEST(ReadyQueueTest, StartsEmpty)
{
    TestPriorityPolicy policy;
    ReadyQueue queue(policy);

    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0U);
}

TEST(ReadyQueueTest, AddsTask)
{
    TestPriorityPolicy policy;
    ReadyQueue queue(policy);

    auto task = std::make_shared<SensorTask>(
        1,
        "Wheel Speed Monitoring",
        SafetyLevel::HIGH,
        2,
        0.0,
        10.0,
        2.0
    );

    queue.addTask(task);

    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 1U);
}

TEST(ReadyQueueTest, ReturnsHighestPriorityTask)
{
    TestPriorityPolicy policy;
    ReadyQueue queue(policy);

    auto lowPriorityTask = std::make_shared<SensorTask>(
        1,
        "Battery Monitoring",
        SafetyLevel::MEDIUM,
        5,
        0.0,
        100.0,
        2.0
    );

    auto highPriorityTask = std::make_shared<SensorTask>(
        2,
        "Airbag Sensor",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        50.0,
        1.0
    );

    queue.addTask(lowPriorityTask);
    queue.addTask(highPriorityTask);

    auto selectedTask = queue.getHighestPriorityTask();

    ASSERT_NE(selectedTask, nullptr);
    EXPECT_EQ(selectedTask->getTaskId(), 2);
}

TEST(ReadyQueueTest, RemovesTaskAfterSelection)
{
    TestPriorityPolicy policy;
    ReadyQueue queue(policy);

    auto task = std::make_shared<SensorTask>(
        3,
        "Engine Temperature",
        SafetyLevel::MEDIUM,
        3,
        0.0,
        100.0,
        4.0
    );

    queue.addTask(task);

    auto selectedTask = queue.getHighestPriorityTask();

    ASSERT_NE(selectedTask, nullptr);
    EXPECT_TRUE(queue.isEmpty());
}

TEST(ReadyQueueTest, ReturnsNullWhenEmpty)
{
    TestPriorityPolicy policy;
    ReadyQueue queue(policy);

    auto selectedTask = queue.getHighestPriorityTask();

    EXPECT_EQ(selectedTask, nullptr);
}