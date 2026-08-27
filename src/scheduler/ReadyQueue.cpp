#include "scheduler/ReadyQueue.h"

ReadyQueue::TaskComparator::TaskComparator(
    const SchedulingPolicy& schedulingPolicy
)
    : policy(schedulingPolicy)
{
}

bool ReadyQueue::TaskComparator::operator()(
    const std::shared_ptr<Task>& first,
    const std::shared_ptr<Task>& second
) const
{
    return policy.higherPriority(second, first);
}

ReadyQueue::ReadyQueue(
    const SchedulingPolicy& schedulingPolicy
)
    : queue(TaskComparator(schedulingPolicy))
{
}

void ReadyQueue::addTask(
    const std::shared_ptr<Task>& task
)
{
    if (task != nullptr)
    {
        queue.push(task);
    }
}

void ReadyQueue::addTasks(
    const std::vector<std::shared_ptr<Task>>& tasks
)
{
    for (const auto& task : tasks)
    {
        addTask(task);
    }
}

std::shared_ptr<Task> ReadyQueue::getHighestPriorityTask()
{
    if (queue.empty())
    {
        return nullptr;
    }

    std::shared_ptr<Task> task = queue.top();
    queue.pop();

    return task;
}

bool ReadyQueue::isEmpty() const
{
    return queue.empty();
}

std::size_t ReadyQueue::size() const
{
    return queue.size();
}

void ReadyQueue::clear()
{
    while (!queue.empty())
    {
        queue.pop();
    }
}