#include "scheduler/FixedPriorityPolicy.h"

bool FixedPriorityPolicy::higherPriority(
    const std::shared_ptr<Task>& first,
    const std::shared_ptr<Task>& second
) const
{
    if (first == nullptr)
    {
        return false;
    }

    if (second == nullptr)
    {
        return true;
    }

    return first->getPriority() < second->getPriority();
}