#include <chrono>
#include <utility>
using namespace std::chrono;
template <class F, class ... Args>
auto test(F f, Args&&... args) {
   auto pre = high_resolution_clock::now();
   auto res = f(std::forward<Args>(args)...);
   auto post = high_resolution_clock::now();
   return make_pair(res, post - pre);
}
#include <thread>
#include <iostream>
using namespace std;
int main() {
   auto res = test([](int n) {
      this_thread::sleep_for(seconds{ n });
      return 3;
   }, 2);
   cout << "Function ran for " << duration_cast<milliseconds>(res.second).count()
        << " ms. and returned " << res.first << endl;
}
