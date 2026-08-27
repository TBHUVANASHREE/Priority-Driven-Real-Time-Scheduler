#include "task/Task.h"

Task::Task(
    int id,
    const std::string& name,
    TaskType type,
    SafetyLevel safety,
    int priority,
    double release,
    double period,
    double execution
)
    : taskId(id),
      taskName(name),
      taskType(type),
      safetyLevel(safety),
      status(TaskStatus::CREATED),
      priority(priority),
      releaseTime(release),
      period(period),
      executionTime(execution),
      remainingTime(execution),
      deadline(release + period),
      nextReleaseTime(release)
{
}

int Task::getTaskId() const
{
    return taskId;
}

const std::string& Task::getTaskName() const
{
    return taskName;
}

TaskType Task::getTaskType() const
{
    return taskType;
}

SafetyLevel Task::getSafetyLevel() const
{
    return safetyLevel;
}

TaskStatus Task::getStatus() const
{
    return status;
}

int Task::getPriority() const
{
    return priority;
}

double Task::getReleaseTime() const
{
    return releaseTime;
}

double Task::getPeriod() const
{
    return period;
}

double Task::getExecutionTime() const
{
    return executionTime;
}

double Task::getRemainingTime() const
{
    return remainingTime;
}

double Task::getDeadline() const
{
    return deadline;
}

double Task::getNextReleaseTime() const
{
    return nextReleaseTime;
}

void Task::setPriority(int priority)
{
    this->priority = priority;
}

void Task::setStatus(TaskStatus status)
{
    this->status = status;
}

void Task::setRemainingTime(double time)
{
    remainingTime = time;

    if (remainingTime <= 0.0)
    {
        remainingTime = 0.0;
        status = TaskStatus::COMPLETED;
    }
}

void Task::setNextReleaseTime(double time)
{
    nextReleaseTime = time;
}

void Task::execute(double time)
{
    if (time <= 0.0 || remainingTime <= 0.0)
    {
        return;
    }

    status = TaskStatus::RUNNING;

    remainingTime -= time;

    if (remainingTime <= 0.0)
    {
        remainingTime = 0.0;
        status = TaskStatus::COMPLETED;
    }
}

void Task::resetExecution()
{
    remainingTime = executionTime;
    status = TaskStatus::READY;
}