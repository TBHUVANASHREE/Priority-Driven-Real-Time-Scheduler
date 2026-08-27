#include "scheduler/RMSPolicy.h"

bool RMSPolicy::higherPriority(
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

    return first->getPeriod() < second->getPeriod();
}