#pragma once

#include <functional>
#include <condition_variable>
#include <queue>
#include <mutex>

class RunnableQueue {

public:
    void runAll();
    void push_back(const std::function<void()> &func);

private:
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<std::function<void()>> queue;
};
