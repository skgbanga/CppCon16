struct X {
  constexpr int f() const { return 3; }
};
struct Y {
  constexpr int g() const { return 4; }
};
struct Z {
  constexpr int h() const { return 5; }
};
struct Chunk : X, Y, Z {
  constexpr Chunk() = default;
};
int main() {
  constexpr Chunk chunk{};
  static_assert(chunk.f() + chunk.g() + chunk.h() == 12, "Suspicious...");
}
