#pragma once

#include <chrono>
#include <iostream>

class Timer final {
private:
    std::chrono::time_point<std::chrono::system_clock> now{std::chrono::system_clock::now()};

public:
    inline void start()
    {
        now = std::chrono::system_clock::now();
    }

    inline double end()
    {
        return static_cast<double>(std::chrono::nanoseconds(std::chrono::system_clock::now() - now).count()) / 1000000000.0;
    }
};
