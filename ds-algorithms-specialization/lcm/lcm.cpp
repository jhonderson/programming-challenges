#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int gcd(int a, int b) {
  if (a < b) {
    swap(a, b);
  }
  int temp;
  while (b != 0) {
    temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

long long lcm_fast(int a, int b) {
  return (long long) a * b / gcd(a, b);
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
