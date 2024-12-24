// ThreadManager.h
#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <atomic>

class ThreadManager
{
private:
    std::vector<std::thread> threads;
    std::atomic<bool> isRunning;
    std::mutex threadMutex;

    ThreadManager();
    ~ThreadManager();

public:
    static ThreadManager& getInstance();

    // Xóa copy constructor và operator=
    ThreadManager(const ThreadManager&) = delete;
    ThreadManager& operator=(const ThreadManager&) = delete;

    void addThread(std::function<void()> task);
    void stopAll();
};
