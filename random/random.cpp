#include <iostream>
#include <random>

int main(int argc, char *argv[])
{
   std::random_device rd; // generate a random device from physical entropy
   std::cout << rd.entropy() << std::endl; // prints 0

   std::mt19937 gen(rd()); // seed the engine with random device

   const int Max = 1000;
   std::uniform_int_distribution<> dis(1, 1000); // generate the distribution 

   const int Num = 500;
   for (int i = 0; i < Num; ++i)
      std::cout << dis(gen) << ' ';

   std::cout << std::endl;

   return 0;
}
