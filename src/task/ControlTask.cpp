#include "task/ControlTask.h"

#include <iostream>

ControlTask::ControlTask(
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
        TaskType::CONTROL,
        safety,
        priority,
        release,
        period,
        execution
    )
{
}

void ControlTask::performTask()
{
    std::cout << "[INFO] Control task executing: "
              << getTaskName() << '\n';
}