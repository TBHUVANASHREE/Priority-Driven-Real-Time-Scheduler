#pragma once

#include <string>

enum class TaskType
{
    SENSOR,
    CONTROL,
    SAFETY
};

enum class SafetyLevel
{
    CRITICAL,
    HIGH,
    MEDIUM,
    LOW
};

enum class TaskStatus
{
    CREATED,
    READY,
    RUNNING,
    PREEMPTED,
    COMPLETED
};

class Task
{
private:
    int taskId;
    std::string taskName;

    TaskType taskType;
    SafetyLevel safetyLevel;
    TaskStatus status;

    int priority;

    double releaseTime;
    double period;
    double executionTime;
    double remainingTime;
    double deadline;
    double nextReleaseTime;

public:
    Task(
        int id,
        const std::string& name,
        TaskType type,
        SafetyLevel safety,
        int priority,
        double release,
        double period,
        double execution
    );

    virtual ~Task() = default;

    int getTaskId() const;
    const std::string& getTaskName() const;

    TaskType getTaskType() const;
    SafetyLevel getSafetyLevel() const;
    TaskStatus getStatus() const;

    int getPriority() const;

    double getReleaseTime() const;
    double getPeriod() const;
    double getExecutionTime() const;
    double getRemainingTime() const;
    double getDeadline() const;
    double getNextReleaseTime() const;

    void setPriority(int priority);
    void setStatus(TaskStatus status);
    void setRemainingTime(double time);
    void setNextReleaseTime(double time);

    void execute(double time);
    void resetExecution();

    virtual void performTask() = 0;
};