#pragma once

#include <memory>
#include <vector>

#include "task/Task.h"

class TaskManager
{
private:
    std::vector<std::shared_ptr<Task>> tasks;

public:
    TaskManager() = default;

    void addTask(const std::shared_ptr<Task>& task);

    bool removeTask(int taskId);

    std::shared_ptr<Task> getTaskById(int taskId) const;

    const std::vector<std::shared_ptr<Task>>& getAllTasks() const;

    std::vector<std::shared_ptr<Task>> getTasksToRelease(double currentTime) const;

    bool isEmpty() const;

    std::size_t getTaskCount() const;
};