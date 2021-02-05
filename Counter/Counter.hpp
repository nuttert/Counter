#pragma once
#include <iostream>
#include <chrono>
#include <unordered_set>
#include <future>
#include <vector>


class Counter
{
    using Sums = std::unordered_multiset<size_t>;
    using Futures = std::vector<std::future<Sums> >;

public:
    Counter() = default;
    void count();

private:
    static constexpr short kNotation = 13;
    static constexpr short kSize = 13;
    static constexpr short kThreads = 3;
};
