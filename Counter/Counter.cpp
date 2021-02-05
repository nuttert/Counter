#include "Counter.hpp"
#include <mutex>

namespace
{
    template <typename T>
    auto getUnion(const std::unordered_multiset<T> &a, const std::unordered_multiset<T> &b)
    {
        std::unordered_multiset<T> result = a;
        result.insert(b.begin(), b.end());
        return result;
    }
} // namespace

void Counter::count()
{
    Futures futures{};
    futures.reserve(kThreads);

    std::mutex mutex;

    for (size_t thread_number = 0; thread_number < kThreads; ++thread_number)
    {
        auto future = std::async([&mutex, thread_number]() -> Sums {
            Sums sums{};
            auto from = static_cast<short>((kNotation ) * (thread_number) / kThreads);
            auto to = static_cast<short>((kNotation ) * (thread_number + 1) / kThreads);

            auto sum = 0;
            {
                std::unique_lock<std::mutex> lock{mutex};
                std::cout << "Thread: " << thread_number << " , from: " << from << ", to: " << to << std::endl;
            }
            for (short i1 = from; i1 < to; ++i1)
            {
                sum += i1;
                for (short i2 = 0; i2 < kNotation ; ++i2)
                {
                    sum += i2;
                    for (short i3 = 0; i3 < kNotation ; ++i3)
                    {
                        sum += i3;
                        for (short i4 = 0; i4 < kNotation ; ++i4)
                        {
                            sum += i4;
                            for (short i5 = 0; i5 < kNotation ; ++i5)
                            {
                                sum += i5;
                                for (short i6 = 0; i6 < kNotation ; ++i6)
                                {
                                    sum += i6;
                                    sums.insert(sum);
                                    sum -= i6;
                                }
                                sum -= i5;
                            }
                            sum -= i4;
                        }
                        sum -= i3;
                    }
                    sum -= i2;
                }
                sum -= i1;
            }
            return sums;
        });
        futures.push_back(std::move(future));
    }

    Sums common_set{};
    for (auto &&future : futures)
    {
        Sums set = future.get();
        auto union_set = getUnion(common_set, set);
        common_set = std::move(union_set);
    }

    long long counter = 0;
    for (size_t sum = 0; sum < (kNotation * short(kNotation / 2)); ++sum)
    {
        counter += common_set.count(sum) * common_set.count(sum);
    }
    std::cout << counter << std::endl;
}