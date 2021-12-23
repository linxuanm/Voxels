#pragma once

#include <functional>
#include <queue>
#include <mutex>

class RunnableQueue {

public:
    void runAll();
    void push_back(const std::function<void()> &func);

private:
    std::mutex mutex;
    std::queue<std::function<void()>> queue;
};
