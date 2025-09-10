#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <optional>
#include "logger.h"
class PipeManager
{
public:
    static PipeManager& getInstance();
    static bool isUsingPipes();

    void start();
    void stop();

    bool isFeatureEnabled(const std::string& featureName) const;
    void setFeatureState(const std::string& featureName, bool enabled);
    void runServer();
    void handleClient(HANDLE hPipe);
    // Prevent copying
    PipeManager(const PipeManager&) = delete;
    PipeManager& operator=(const PipeManager&) = delete;

    // Prevent moving
    PipeManager(PipeManager&&) = delete;
    PipeManager& operator=(PipeManager&&) = delete;

private:
    PipeManager();
    ~PipeManager();

    std::atomic<bool> m_running{false};
    std::thread m_serverThread;
    std::unordered_map<std::string, bool> m_features;
    mutable std::mutex m_featuresMutex;

    static constexpr auto PIPE_NAME = L"\\\\.\\pipe\\JMNX0034";
    static constexpr auto PIPE_FLAG_NAME = "UsePipeModeFlag_";
};
