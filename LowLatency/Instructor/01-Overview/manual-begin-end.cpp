#include <vector>
#include <algorithm>
#include <cstdio>
int main() {
  using namespace std;
  vector<int> v{ 2,3,5,7,11 };
  int arr[] { 2,3,5,7,11 };
  enum { N = sizeof(arr) / sizeof(arr[0]) };
  int sumA = 0;
  for(auto it = v.begin(); it != v.end(); ++it)
    sumA += *it;
  int sumB = 0;
  for(auto it = arr + 0; it != arr + N; ++it)
    sumB += *it;
  printf("%d %d", sumA, sumB);
}