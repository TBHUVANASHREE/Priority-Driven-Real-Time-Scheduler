#include "configuration/ConfigManager.h"

#include <fstream>

bool ConfigManager::loadConfiguration(const std::string& filePath)
{
    std::ifstream configurationFile(filePath);

    if (!configurationFile.is_open())
    {
        return false;
    }

    configurationFilePath = filePath;

    return true;
}

bool ConfigManager::validateConfiguration(
    const std::vector<std::shared_ptr<Task>>& tasks
) const
{
    if (tasks.empty())
    {
        return false;
    }

    for (const auto& task : tasks)
    {
        if (task == nullptr)
        {
            return false;
        }

        if (task->getTaskId() <= 0)
        {
            return false;
        }

        if (task->getPriority() <= 0)
        {
            return false;
        }

        if (task->getExecutionTime() <= 0.0)
        {
            return false;
        }

        if (task->getPeriod() <= 0.0)
        {
            return false;
        }
    }

    return true;
}

const std::string& ConfigManager::getConfigurationFilePath() const
{
    return configurationFilePath;
}