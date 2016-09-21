//
// homemade version, prefer (by far!) std::optional<T>
//
#include <cassert>
#include <ostream>
#include <memory>
template <class T>
class maybe {
   bool empty_;
   std::aligned_storage_t<sizeof(T), alignof(T)> buf;
   constexpr void* as_raw() {
      return static_cast<void*>(&buf);
   }
   T* as_pointer() {
      return reinterpret_cast<T*>(&buf);
   }
   const T* as_pointer() const {
      return reinterpret_cast<const T*>(&buf);
   }
public:
   constexpr bool empty() const noexcept {
      return empty_;
   }
   constexpr operator bool() const noexcept {
      return !empty();
   }
   constexpr maybe() : empty_{ true } {
   }
   constexpr maybe(std::nullptr_t) : empty_{ true } {
   }
   maybe& operator=(std::nullptr_t) {
      if (!empty()) as_pointer()->~T();
      vide = true;
      return *this;
   }
   constexpr maybe(const T &val) : empty_{ false } {
      new (as_raw()) T(val);
   }
   constexpr maybe(T &&val) : empty_{ false } {
      new (as_raw()) T(std::move(val));
   }
   maybe& operator=(const T &val) {
      if (!empty()) as_pointer()->~T();
      new (as_raw()) T(val);
      empty_ = {};
      return *this;
   }
   maybe(const maybe &val)
      : empty_{ val.empty() }
   {
      if (!empty())
         new (as_raw()) T(static_cast<const T&>(val));
   }
   maybe& operator=(const maybe &other) {
      if (!empty()) as_pointer()->~T();
      if (other.empty())
         vide = true;
      else {
         new (as_raw()) T(static_cast<const T&>(other));
         vide = {};
      }
      return *this;
   }
   ~maybe() {
      if (!empty())
         as_pointer()->~T();
   }
   constexpr explicit operator T&() {
      assert(!empty());
      return *as_pointer();
   }
   constexpr explicit operator const T&() const {
      assert(!empty());
      return *as_pointer();
   }
   constexpr T* operator->() {
      assert(!empty());
      return as_pointer();
   }
   constexpr const T* operator->() const {
      assert(!empty());
      return as_pointer();
   }
   friend std::ostream& operator<<(std::ostream &os, const maybe<T> &m) {
      return os << static_cast<const T&>(m);
   }
};

class divide_by_zero {};
maybe<int> integral_division(int num, int denom) {
   return !denom ? maybe<int>{ } : maybe<int>{ num / denom };
}

#include <iostream>
   int main() {
      using namespace std;
      int n, d;
      if (cin >> n >> d) {
         auto res = integral_division(n, d);
         if (res)
            cout << "Result : " << static_cast<int>(res) << endl;
         else
            cout << "Divide by zero" << endl;
      }
   }
