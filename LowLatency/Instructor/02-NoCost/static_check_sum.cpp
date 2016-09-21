template <int ... Is>
  constexpr auto sum() {
     int vals[] { Is... };
     long result {};
     for(auto val : vals) result += val;
     return result;
  }
int main() {
  constexpr auto res = sum<2,3,5,7,11>();
  static_assert(res == 28, "Suspicious...");
}