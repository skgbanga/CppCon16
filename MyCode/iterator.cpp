#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    std::vector<int>::iterator a_iter;
    std::vector<int> b;
    {
        std::vector<int> a{1, 2, 10, 4, 5};
        std::cout << "Before A " << &a[0] << std::endl;
        a_iter = a.begin() + 2;
        b = std::move(a);
        std::cout << "After A " << &a[0] << std::endl;
        std::cout << "After B " << &b[0] << std::endl;
    }
    std::cout << *a_iter << std::endl;
    return 0;
}
