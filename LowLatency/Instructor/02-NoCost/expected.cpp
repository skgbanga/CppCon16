#include <memory>

template <class T>
constexpr T max_(T a, T b) { return a < b ? b : a; }

template <class T, class E>
class expected {
   std::aligned_storage_t<max_(sizeof(T), sizeof(E)), max_(alignof(T), alignof(E))> buf;
   constexpr const void * as_raw() const {
      return static_cast<const void*>(&buf);
   }
   constexpr void * as_raw() {
      return static_cast<void*>(&buf);
   }
public:
   enum owns_what : bool { has_value, has_alternative };
private:
   owns_what owns;
public:
   expected(const expected &other) : owns{ other.owns } {
      if (owns_value())
         new (as_raw()) T{ other.value() };
      else
         new (as_raw()) E{ other.alternative() };
   }
   ~expected() {
      if (owns_value())
         static_cast<T*>(as_raw())->~T();
      else
         static_cast<E*>(as_raw())->~E();
   }
   expected& operator=(const expected &other) { // brittle
      if (this != &other) {
         if (owns_value())
            static_cast<T*>(as_raw())->~T();
         else
            static_cast<E*>(as_raw())->~E();
         owns = other.owns;
         if (owns_value())
            new (as_raw()) T{ other.value() };
         else
            new (as_raw()) E{ other.alternative() };
      }
   }
   constexpr expected(const T &val) : owns{ has_value } {
      new (as_raw()) T{ val };
   }
   constexpr expected(T &&val) : owns{ has_value } {
      new (as_raw()) T{ std::move(val) };
   }
   constexpr expected(const E &val) : owns{ has_alternative } {
      new (as_raw()) E{ val };
   }
   constexpr expected(E &&val) : owns{ has_alternative } {
      new (as_raw()) E{ std::move(val) };
   }
   // In case of is_same_v<T,E>
   constexpr expected(const T &val, owns_what owns) : owns{ owns } {
      new (as_raw()) T{ val };
   }
   constexpr expected(T &&val, owns_what owns) : owns{ owns } {
      new (as_raw()) T{ std::move(val) };
   }
   constexpr bool owns_value() const noexcept {
      return owns == has_value;
   }
   constexpr bool owns_alternative() const noexcept {
      return !owns_value();
   }
   constexpr operator bool() const noexcept {
      return owns_value();
   }
   constexpr const T &value() const {
      return *static_cast<const T*>(as_raw());
   }
   constexpr const E &alternative() const {
      return *static_cast<const E*>(as_raw());
   }
};

class divide_by_zero {};
expected<int, divide_by_zero> integral_division(int num, int denom) {
   return !denom ? expected<int, divide_by_zero>{ divide_by_zero{} } : expected<int, divide_by_zero>{ num / denom };
}

#include <iostream>
int main() {
   using namespace std;
   int n, d;
   if (cin >> n >> d) {
      auto e = integral_division(n, d);
      if (e)
         cout << "Result : " << e.value() << endl;
      else
         cout << "Divide by zero" << endl;
   }
}
