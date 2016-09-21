static_assert(static_cast<char>(-1) < 0,
   "Signed char required");
// ...
static_assert(sizeof(int) == sizeof(int*),
   "Expect same size for pointers and ints");
// ...
#include <type_traits>
#include <algorithm>
template <class T>
unsigned char* raw_copy(const T &val, unsigned char *buf) {
   static_assert(std::is_trivially_copyable_v<T>,
      "Function requires bitwise copyable type");
   auto src = reinterpret_cast<const unsigned char*>(&val);
   std::copy(src, src + sizeof val, buf);
   return buf + sizeof val;
}
#include <string>
int main() {
   int n = 0x01020304;
   unsigned char buf0[sizeof n];
   raw_copy(n, buf0);
   //std::string s = "I love my teacher";
   //unsigned char buf1[sizeof s]; // suspicious...
   // raw_copy(s, buf1); // uncomment to see the effect
}