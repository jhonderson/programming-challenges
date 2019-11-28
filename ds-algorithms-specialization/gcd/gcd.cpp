#include <iostream>

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast_recursive(int a, int b) {
  if (a < b) {
    swap(a, b);
  }
  if (b == 0) {
    return a;
  }
  return gcd_fast_recursive(b, a % b);
}

int gcd_fast_iterative(int a, int b) {
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

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_fast_iterative(a, b) << std::endl;
  return 0;
}
