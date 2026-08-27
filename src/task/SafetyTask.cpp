#include "task/SafetyTask.h"

#include <iostream>

SafetyTask::SafetyTask(
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
        TaskType::SAFETY,
        safety,
        priority,
        release,
        period,
        execution
    )
{
}

void SafetyTask::performTask()
{
    std::cout << "[INFO] Safety task executing: "
              << getTaskName() << '\n';
}