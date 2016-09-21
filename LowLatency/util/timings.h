#include <chrono>
#include <utility>

template <class F, class ... Args>
auto test(F f, Args&&... args)
{
   auto pre = std::chrono::high_resolution_clock::now();
   auto res = f(std::forward<Args>(args)...);
   auto post = std::chrono::high_resolution_clock::now();
   return std::make_pair(std::move(res), post - pre);
}

