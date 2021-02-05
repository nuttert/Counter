#include <iostream>
#include <chrono>
#include <unordered_set>
#include <future>
#include <vector>

#include "Counter/Counter.hpp"

int main()
{
    Counter counter;
    counter.count();
    return 0;
}