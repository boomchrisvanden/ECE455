#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>

const int maxItems = 10; 

std::queue<int> itemQueue;
std::mutex mtx;
std::condition_variable cv;
bool done = false; 


void producer() {
    for (int i = 0; i < 100; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return itemQueue.size() < maxItems; });
        itemQueue.push(i);
        std::cout << "Produced: " << i << "\n";
        lock.unlock();
        cv.notify_all();
    } 
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !itemQueue.empty() || done; });
        if (!itemQueue.empty()) {
            int item = itemQueue.front();
            itemQueue.pop();
            std::cout << "Consumed: " << item << "\n";
            lock.unlock();
            cv.notify_all();
        } else if (done) {
            break;
        }
    }
}

int main() {
    std::thread prodThread(producer);
    std::thread consThread(consumer);

    prodThread.join();
    consThread.join();

    return 0;
}