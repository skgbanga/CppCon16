#include <iostream>
#include <limits>


int main()
{
    int16_t mi = std::numeric_limits<int16_t>::min();
    int16_t ma = std::numeric_limits<int16_t>::max();
    int16_t temp = -1 * mi;
    std::cout << mi << std::endl;
    std::cout << ma << std::endl;
    std::cout << temp << std::endl;
}
