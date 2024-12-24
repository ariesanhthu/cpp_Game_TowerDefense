// ThreadManager.cpp
#include "ThreadManager.h"

ThreadManager::ThreadManager()
{
    isRunning = true;
}

ThreadManager::~ThreadManager()
{
    stopAll();
}

ThreadManager& ThreadManager::getInstance()
{
    static ThreadManager instance;
    return instance;
}

void ThreadManager::addThread(std::function<void()> task)
{
    std::lock_guard<std::mutex> lock(threadMutex);

    threads.emplace_back([this, task]()
        {
            while (isRunning)
            {
                task();
            }
        });
}

void ThreadManager::stopAll()
{
    isRunning = false;

    std::lock_guard<std::mutex> lock(threadMutex);
    for (auto& t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    threads.clear();
}
