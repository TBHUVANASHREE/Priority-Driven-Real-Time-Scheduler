#pragma once

#include <memory>

#include "scheduler/SchedulingPolicy.h"

class FixedPriorityPolicy : public SchedulingPolicy
{
public:
    bool higherPriority(
        const std::shared_ptr<Task>& first,
        const std::shared_ptr<Task>& second
    ) const override;
};