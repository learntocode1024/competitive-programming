#include "io"
#include "poly/poly_sqrt.hpp"

typedef poly<mint> FPS;
int main() {
  IO::init_in();
  int n = rd();
  FPS a(n);
  for (int i = 0, t; i < n; ++i) {
    a[i] = rd();
  }
  FPS b = sqrt(a);
  print(b);
}