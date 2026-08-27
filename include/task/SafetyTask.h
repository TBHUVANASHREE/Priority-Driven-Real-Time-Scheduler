#pragma once

#include "task/Task.h"

class SafetyTask : public Task
{
public:
    SafetyTask(
        int id,
        const std::string& name,
        SafetyLevel safety,
        int priority,
        double release,
        double period,
        double execution
    );

    void performTask() override;
};