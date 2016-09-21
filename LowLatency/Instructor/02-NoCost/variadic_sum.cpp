#include <cstdio>
template <class T>
  constexpr T sum(T arg) {
    return arg;
  }
template <class T, class ... Ts>
  constexpr auto sum(T arg, Ts ... args) {
     return arg + sum(args...);
  }
int main() {
  constexpr int result = sum(2,3,5,7,11);
  std::printf("%d", result);
}