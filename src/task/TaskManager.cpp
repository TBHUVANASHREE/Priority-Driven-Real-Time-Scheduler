#include "task/TaskManager.h"

void TaskManager::addTask(const std::shared_ptr<Task>& task)
{
    if (task != nullptr)
    {
        tasks.push_back(task);
    }
}

bool TaskManager::removeTask(int taskId)
{
    for (auto iterator = tasks.begin(); iterator != tasks.end(); ++iterator)
    {
        if ((*iterator)->getTaskId() == taskId)
        {
            tasks.erase(iterator);
            return true;
        }
    }

    return false;
}

std::shared_ptr<Task> TaskManager::getTaskById(int taskId) const
{
    for (const auto& task : tasks)
    {
        if (task->getTaskId() == taskId)
        {
            return task;
        }
    }

    return nullptr;
}

const std::vector<std::shared_ptr<Task>>& TaskManager::getAllTasks() const
{
    return tasks;
}

std::vector<std::shared_ptr<Task>> TaskManager::getTasksToRelease(
    double currentTime
) const
{
    std::vector<std::shared_ptr<Task>> releasedTasks;

    for (const auto& task : tasks)
    {
        if (task->getNextReleaseTime() <= currentTime)
        {
            releasedTasks.push_back(task);
        }
    }

    return releasedTasks;
}

bool TaskManager::isEmpty() const
{
    return tasks.empty();
}

std::size_t TaskManager::getTaskCount() const
{
    return tasks.size();
}