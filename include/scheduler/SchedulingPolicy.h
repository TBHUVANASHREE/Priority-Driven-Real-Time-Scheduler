#pragma once

#include <memory>

#include "task/Task.h"

class SchedulingPolicy
{
public:
    virtual ~SchedulingPolicy() = default;

    virtual bool higherPriority(
        const std::shared_ptr<Task>& first,
        const std::shared_ptr<Task>& second
    ) const = 0;
};