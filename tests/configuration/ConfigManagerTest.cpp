#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "configuration/ConfigManager.h"
#include "task/SensorTask.h"
#include "task/SafetyTask.h"

TEST(ConfigManagerTest, LoadsExistingConfigurationFile)
{
    ConfigManager manager;

    EXPECT_TRUE(manager.loadConfiguration("config/tasks.txt"));
    EXPECT_EQ(
        manager.getConfigurationFilePath(),
        "config/tasks.txt"
    );
}

TEST(ConfigManagerTest, RejectsMissingConfigurationFile)
{
    ConfigManager manager;

    EXPECT_FALSE(
        manager.loadConfiguration("config/missing.txt")
    );
}

TEST(ConfigManagerTest, AcceptsValidTaskConfiguration)
{
    ConfigManager manager;

    std::vector<std::shared_ptr<Task>> tasks;

    tasks.push_back(
        std::make_shared<SensorTask>(
            1,
            "Wheel Speed Monitoring",
            SafetyLevel::HIGH,
            2,
            0.0,
            10.0,
            2.0
        )
    );

    EXPECT_TRUE(manager.validateConfiguration(tasks));
}

TEST(ConfigManagerTest, RejectsEmptyTaskConfiguration)
{
    ConfigManager manager;

    std::vector<std::shared_ptr<Task>> tasks;

    EXPECT_FALSE(manager.validateConfiguration(tasks));
}

TEST(ConfigManagerTest, RejectsInvalidTaskPriority)
{
    ConfigManager manager;

    std::vector<std::shared_ptr<Task>> tasks;

    tasks.push_back(
        std::make_shared<SafetyTask>(
            2,
            "Airbag Monitoring",
            SafetyLevel::CRITICAL,
            0,
            0.0,
            50.0,
            3.0
        )
    );

    EXPECT_FALSE(manager.validateConfiguration(tasks));
}