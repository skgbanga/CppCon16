#include <iostream>

struct NoMove {
   NoMove() = default;
    // prevents implicit declaration of default move constructor
    // however, the class is still move-constructible because its
    // copy constructor can bind to an rvalue argument
    NoMove(NoMove&&) = delete;
};


int main(int argc, char *argv[])
{
   NoMove first;
   NoMove second = std::move(first);
   return 0;
}
