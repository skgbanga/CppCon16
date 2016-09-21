#include "util/timings.h"

#include <iostream>
#include <chrono>

struct foo
{
   foo() = default;
   foo(const foo&) = delete;
   foo(foo&&) = default;
};

foo func()
{
   return foo{};
}

int main(int argc, char *argv[])
{
   auto ret = test(func);
   std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(ret.second).count();
}
