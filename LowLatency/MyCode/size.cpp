#include <iostream>

struct foo
{
   int n {10};
};

struct bar : virtual foo
{  };

struct baz : virtual foo
{  };

struct qux : bar, baz
{  };

int main(int argc, char *argv[])
{

   std::cout << sizeof(foo) << '\n';
   std::cout << sizeof(bar) << '\n';
   std::cout << sizeof(baz) << '\n';
   std::cout << sizeof(qux) << '\n';

   return 0;
}
