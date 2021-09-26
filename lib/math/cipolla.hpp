#pragma once

#include <cstdlib>
#include <ctime>
#include <utility>
#include "../utils"

int cipolla(int n, int p) { // p is an odd prime
  auto q_pow = [](i64 x, int a, int p) {
    i64 ret = 1;
    while (a) {
      if (a & 1) ret = ret * x % p;
      x = x * x % p;
      a >>= 1;
    }
    return ret;
  };
  if (q_pow(n, (p-1)>>1, p) == p - 1) return -1;
  if (n == 0) return 0;
  srand(time(0));
  i64 a, w = -1;
  while (w == -1) {
    a = rand() % (p - 1) + 1;
    w = (a * a - n + p) % p;
    if (q_pow(w, (p-1)>>1, p) == 1) w = -1;
  }
  int t = (p+1) >> 1;
  pair<i64, i64> x(1, 0), y(a, 1);
  auto mul = [w, p] (pair<i64, i64> a, pair<i64, i64> b) {
    pair<i64, i64> ret;
    ret.fi = (a.fi * b.fi + a.se * b.se % p * w) % p;
    ret.se = (a.fi * b.se + a.se * b.fi) % p;
    return ret;
  };
  while (t) {
    if (t & 1) x = mul(x, y);
    y = mul(y, y);
    t >>= 1;
  }
  return x.fi;
}