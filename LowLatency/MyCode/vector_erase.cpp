#include <vector>
#include <iostream>
#include <memory>

struct Noisy
{
   Noisy(int i)
      : i_(i)
   {
      std::cout << "Default constructor called " << i << std::endl;
   }
   /* Noisy(const Noisy&) { std::cout << "copy ctor called" << std::endl; } */
   /* Noisy& operator=(const Noisy&) { std::cout << "copy assignment called" << std::endl; return *this; } */
   /* Noisy(Noisy&&) noexcept { std::cout << "move ctor called" << std::endl; } */
   /* Noisy& operator=(Noisy&&) noexcept { std::cout << "copy assignment called" << std::endl; return *this; } */
   ~Noisy() { std::cout << "dtor called " << i_ << std::endl; }

   /* void set_ptr(std::shared_ptr<Noisy> ptr) */
   /* { */
   /*    ptr_ = ptr; */
   /* } */

   /* std::weak_ptr<Noisy> ptr_; */
   int i_;
};


int main(int argc, char *argv[])
{
   std::vector<Noisy> vecs;
   vecs.emplace_back(1);
   vecs.emplace_back(2);
   vecs.emplace_back(3);
   /* auto sp1 = std::make_shared<Noisy>(10); */
   /* auto sp2 = std::make_shared<Noisy>(20); */

   /* // create a cycle */
   /* sp1->set_ptr(sp2); */
   /* sp2->set_ptr(sp1); */

   // now dtor's are not called
   return 0;
}
