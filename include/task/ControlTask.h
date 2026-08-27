#pragma once

#include "task/Task.h"

class ControlTask : public Task
{
public:
    ControlTask(
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