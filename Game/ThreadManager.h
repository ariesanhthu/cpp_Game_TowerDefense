#pragma once
#include <thread>
#include <vector>
#include <functional>

class ThreadManager {
private:
    std::vector<std::thread> threads;

public:
    ~ThreadManager();
    void addThread(std::function<void()> func);
    void joinAll();
};
