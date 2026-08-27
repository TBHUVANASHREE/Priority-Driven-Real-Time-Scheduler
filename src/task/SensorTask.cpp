#include "task/SensorTask.h"

#include <iostream>

SensorTask::SensorTask(
    int id,
    const std::string& name,
    SafetyLevel safety,
    int priority,
    double release,
    double period,
    double execution
)
    : Task(
        id,
        name,
        TaskType::SENSOR,
        safety,
        priority,
        release,
        period,
        execution
    )
{
}

void SensorTask::performTask()
{
    std::cout << "[INFO] Sensor task executing: "
              << getTaskName() << '\n';
}