#pragma once

#include <memory>
#include <string>
#include <vector>

#include "task/Task.h"

class ConfigManager
{
private:
    std::string configurationFilePath;

public:
    ConfigManager() = default;

    bool loadConfiguration(const std::string& filePath);

    bool validateConfiguration(
        const std::vector<std::shared_ptr<Task>>& tasks
    ) const;

    const std::string& getConfigurationFilePath() const;
};