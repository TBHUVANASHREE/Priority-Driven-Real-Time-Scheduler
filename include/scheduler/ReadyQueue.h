#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "scheduler/SchedulingPolicy.h"
#include "task/Task.h"

class ReadyQueue
{
private:
    class TaskComparator
    {
    private:
        const SchedulingPolicy& policy;

    public:
        explicit TaskComparator(const SchedulingPolicy& schedulingPolicy);

        bool operator()(
            const std::shared_ptr<Task>& first,
            const std::shared_ptr<Task>& second
        ) const;
    };

    std::priority_queue<
        std::shared_ptr<Task>,
        std::vector<std::shared_ptr<Task>>,
        TaskComparator
    > queue;

public:
    explicit ReadyQueue(const SchedulingPolicy& schedulingPolicy);

    void addTask(const std::shared_ptr<Task>& task);

    void addTasks(
        const std::vector<std::shared_ptr<Task>>& tasks
    );

    std::shared_ptr<Task> getHighestPriorityTask();

    bool isEmpty() const;

    std::size_t size() const;

    void clear();
};