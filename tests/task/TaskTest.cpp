#include <gtest/gtest.h>
#include <memory>

#include "task/TaskManager.h"
#include "task/SensorTask.h"
#include "task/ControlTask.h"
#include "task/SafetyTask.h"

TEST(TaskTest, CreatesSensorTaskCorrectly)
{
    SensorTask task(
        1,
        "Wheel Speed Monitoring",
        SafetyLevel::HIGH,
        2,
        0.0,
        10.0,
        2.0
    );

    EXPECT_EQ(task.getTaskId(), 1);
    EXPECT_EQ(task.getTaskName(), "Wheel Speed Monitoring");
    EXPECT_EQ(task.getTaskType(), TaskType::SENSOR);
    EXPECT_EQ(task.getSafetyLevel(), SafetyLevel::HIGH);
    EXPECT_EQ(task.getPriority(), 2);
}

TEST(TaskTest, CreatesControlTaskCorrectly)
{
    ControlTask task(
        2,
        "Brake Control",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        20.0,
        5.0
    );

    EXPECT_EQ(task.getTaskId(), 2);
    EXPECT_EQ(task.getTaskName(), "Brake Control");
    EXPECT_EQ(task.getTaskType(), TaskType::CONTROL);
    EXPECT_EQ(task.getSafetyLevel(), SafetyLevel::CRITICAL);
    EXPECT_EQ(task.getPriority(), 1);
}

TEST(TaskTest, CreatesSafetyTaskCorrectly)
{
    SafetyTask task(
        3,
        "Airbag Monitoring",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        50.0,
        3.0
    );

    EXPECT_EQ(task.getTaskId(), 3);
    EXPECT_EQ(task.getTaskName(), "Airbag Monitoring");
    EXPECT_EQ(task.getTaskType(), TaskType::SAFETY);
    EXPECT_EQ(task.getSafetyLevel(), SafetyLevel::CRITICAL);
    EXPECT_EQ(task.getPriority(), 1);
}

TEST(TaskTest, InitialRemainingTimeMatchesExecutionTime)
{
    SensorTask task(
        4,
        "Engine Temperature Monitoring",
        SafetyLevel::MEDIUM,
        3,
        0.0,
        100.0,
        4.0
    );

    EXPECT_DOUBLE_EQ(task.getRemainingTime(), 4.0);
}

TEST(TaskTest, ExecutesTaskAndUpdatesRemainingTime)
{
    SensorTask task(
        5,
        "Vehicle Speed Monitoring",
        SafetyLevel::HIGH,
        2,
        0.0,
        10.0,
        5.0
    );

    task.execute(2.0);

    EXPECT_DOUBLE_EQ(task.getRemainingTime(), 3.0);
    EXPECT_EQ(task.getStatus(), TaskStatus::RUNNING);
}

TEST(TaskTest, TaskCompletesWhenExecutionTimeIsFinished)
{
    ControlTask task(
        6,
        "Steering Control",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        20.0,
        3.0
    );

    task.execute(3.0);

    EXPECT_DOUBLE_EQ(task.getRemainingTime(), 0.0);
    EXPECT_EQ(task.getStatus(), TaskStatus::COMPLETED);
}

TEST(TaskTest, ResetExecutionMakesTaskReady)
{
    SafetyTask task(
        7,
        "Airbag System",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        50.0,
        3.0
    );

    task.execute(3.0);
    task.resetExecution();

    EXPECT_DOUBLE_EQ(task.getRemainingTime(), 3.0);
    EXPECT_EQ(task.getStatus(), TaskStatus::READY);
}

TEST(TaskTest, TaskPriorityCanBeUpdated)
{
    SensorTask task(
        8,
        "Fuel Level Monitoring",
        SafetyLevel::LOW,
        5,
        0.0,
        100.0,
        2.0
    );

    task.setPriority(2);

    EXPECT_EQ(task.getPriority(), 2);
}
TEST(TaskManagerTest, AddsTasksSuccessfully)
{
    TaskManager manager;

    auto sensorTask = std::make_shared<SensorTask>(
        10,
        "Wheel Speed Monitoring",
        SafetyLevel::HIGH,
        2,
        0.0,
        10.0,
        2.0
    );

    manager.addTask(sensorTask);

    EXPECT_EQ(manager.getTaskCount(), 1U);
    EXPECT_FALSE(manager.isEmpty());
}
TEST(TaskManagerTest, FindsTaskById)
{
    TaskManager manager;

    auto controlTask = std::make_shared<ControlTask>(
        11,
        "Brake Control",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        20.0,
        5.0
    );

    manager.addTask(controlTask);

    auto result = manager.getTaskById(11);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getTaskName(), "Brake Control");
}
TEST(TaskManagerTest, ReturnsNullForUnknownTaskId)
{
    TaskManager manager;

    auto result = manager.getTaskById(999);

    EXPECT_EQ(result, nullptr);
}
TEST(TaskManagerTest, RemovesTaskSuccessfully)
{
    TaskManager manager;

    auto safetyTask = std::make_shared<SafetyTask>(
        12,
        "Airbag Monitoring",
        SafetyLevel::CRITICAL,
        1,
        0.0,
        50.0,
        3.0
    );

    manager.addTask(safetyTask);

    EXPECT_TRUE(manager.removeTask(12));
    EXPECT_EQ(manager.getTaskCount(), 0U);
}
TEST(TaskManagerTest, ReturnsFalseWhenRemovingUnknownTask)
{
    TaskManager manager;

    EXPECT_FALSE(manager.removeTask(999));
}
TEST(TaskManagerTest, ReturnsTasksReadyForRelease)
{
    TaskManager manager;

    auto sensorTask = std::make_shared<SensorTask>(
        13,
        "Engine Temperature Monitoring",
        SafetyLevel::MEDIUM,
        3,
        5.0,
        100.0,
        4.0
    );

    manager.addTask(sensorTask);

    auto releasedTasks = manager.getTasksToRelease(5.0);

    ASSERT_EQ(releasedTasks.size(), 1U);
    EXPECT_EQ(releasedTasks.front()->getTaskId(), 13);
}