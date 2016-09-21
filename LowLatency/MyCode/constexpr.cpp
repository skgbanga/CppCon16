#include <iostream>

template <typename T>
constexpr bool close_enough(T a, T b)
{
   return a == b;
}

int main(int argc, char *argv[])
{
   static_assert(close_enough(4, 4), "");
   return 0;
}
