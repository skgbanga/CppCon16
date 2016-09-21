#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <util/timings.h>

auto sqm = [](auto x)
{
   return std::sqrt(x);
};

std::vector<double> f1(std::vector<double> vs)
{
   std::transform(vs.begin(), vs.end(), vs.begin(), sqm);
   return vs;
}

void f2(std::vector<double>& vs)
{
   std::transform(vs.begin(), vs.end(), vs.begin(), sqm);
}

int main(int argc, char *argv[])
{
   static constexpr int N = 10000000;
   std::vector<double> vs (N);
   std::iota(vs.begin(), vs.end(), 1.0);

   // case 1
   auto l1 = [vs]()
   {
      auto result = f1(vs);
      return result.back();
   };
   auto r1 = test(l1);
   std::cout << "Time for " << r1.first << " "
      << std::chrono::duration_cast<std::chrono::microseconds>(r1.second).count() << std::endl;

   // case 2
   auto l2 = [vs]() mutable
   {
      f2(vs);
      return vs.back();
   };
   auto r2 = test(l2);
   std::cout << "Time for " << r2.first << " "
      << std::chrono::duration_cast<std::chrono::microseconds>(r2.second).count() << std::endl;

   // case 2
   auto l3 = [vs]() mutable
   {
      auto result = f1(std::move(vs));
      return result.back();
   };
   auto r3 = test(l3);
   std::cout << "Time for " << r3.first << " "
      << std::chrono::duration_cast<std::chrono::microseconds>(r3.second).count() << std::endl;

   return 0;
}
