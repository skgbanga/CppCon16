#include <iostream>
#include <memory>

struct Base
{
   virtual void func() noexcept
   {
      std::cout << "base called" << std::endl;
   }
};

struct Derived : Base
{
   void func() override
   {
      std::cout << "derived called" << std::endl;
   }
};

int main(int argc, char *argv[])
{
   auto d = std::make_unique<Derived>();
   Base* b = d.get();

   b->func();
   return 0;
}
