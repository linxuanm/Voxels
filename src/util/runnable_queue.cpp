#include "runnable_queue.h"

void RunnableQueue::runAll() {
    std::unique_lock<std::mutex> lock{mutex};

    while (!queue.empty()) {
        queue.front()();
        queue.pop();
    }

    lock.unlock();
}

void RunnableQueue::push_back(const std::function<void()> &func) {
    std::unique_lock<std::mutex> lock{mutex};
    queue.push(func);
    lock.unlock();
}
