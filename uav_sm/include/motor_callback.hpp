#ifndef MOTOR_CALLBACK_HPP_
#define MOTOR_CALLBACK_HPP_

#include <functional>
#include <atomic>
#include <thread>

class CallbackTimer
{
// Source code taken from https://stackoverflow.com/questions/30425772/c-11-calling-a-c-function-periodically
public:
    CallbackTimer() :_execute(false)
    {}

    ~CallbackTimer() {
        if (_execute.load(std::memory_order_acquire)) {
            stop();
        };
    }

    // Join thread and stop
    void stop()
    {
        _execute.store(false, std::memory_order_release);
        if (_thd.joinable()){
            // When you call join() on a thread, the calling thread 
            // (usually the main thread) waits for the child thread to 
            // finish its execution
            _thd.join();
        }
    }

    /**
     * @brief 
     * 
     * @param interval [ms] Interval to wait
     * @param func Function pointer
     */
    void start(int interval, std::function<void(void)> func)
    {   
        // If currently executing, then join thread and wait for it to finish
        if (_execute.load(std::memory_order_acquire)){
            stop();
        };

        _execute.store(true, std::memory_order_release);
        _thd = std::thread([this, interval, func]()
        {
            while (_execute.load(std::memory_order_acquire)) {
                func();
                std::this_thread::sleep_until(
                    std::chrono::steady_clock::now() + std::chrono::milliseconds(interval));
            }
        });
    }

    bool is_running() const noexcept {
        return (_execute.load(std::memory_order_acquire) && _thd.joinable());
    }

private:
    // You need atomic<bool> to avoid race-conditions. 
    // A race-condition occurs if two threads access the same memory location, 
    // and at least one of them is a write operation. 
    std::atomic<bool> _execute;
    std::thread _thd;
};

#endif //MOTOR_CALLBACK_HPP_