cmake_minimum_required(VERSION 3.20)

project(AutomotiveScheduler
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_executable(AutomotiveScheduler
    main.cpp

    src/task/Task.cpp
    src/task/SensorTask.cpp
    src/task/ControlTask.cpp
    src/task/SafetyTask.cpp
    src/task/TaskManager.cpp

    src/configuration/ConfigManager.cpp

    src/simulation/VirtualClock.cpp

    src/scheduler/ReadyQueue.cpp
    src/scheduler/FixedPriorityPolicy.cpp
    src/scheduler/RMSPolicy.cpp
)

target_include_directories(AutomotiveScheduler
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
add_executable(TaskTests
    tests/task/TaskTest.cpp
    
    tests/configuration/ConfigManagerTest.cpp
    
    tests/simulation/VirtualClockTest.cpp
    
    tests/scheduler/ReadyQueueTest.cpp
    tests/scheduler/FixedPriorityPolicyTest.cpp
    tests/scheduler/RMSPolicyTest.cpp

    src/task/Task.cpp
    src/task/SensorTask.cpp
    src/task/ControlTask.cpp
    src/task/SafetyTask.cpp
    src/task/TaskManager.cpp

    src/configuration/ConfigManager.cpp

    src/simulation/VirtualClock.cpp

    src/scheduler/ReadyQueue.cpp
    src/scheduler/FixedPriorityPolicy.cpp
    src/scheduler/RMSPolicy.cpp
)

target_include_directories(TaskTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(TaskTests
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(
    TaskTests
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)