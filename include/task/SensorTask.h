#pragma once

#include "task/Task.h"

class SensorTask : public Task
{
public:
    SensorTask(
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