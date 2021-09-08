#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "io"
#include "utils"

const int N = 4000005;
int mod;
int c[N];
int n;
 
inline int reduce(int x) {
  if (x >= mod) return x - mod;
  return x;
}
 
inline int add(int x, int y) {
  return reduce(x + y);
}
 
inline int del(int x, int y) {
  return reduce(x - y + mod);
}
 
int get(int x) {
  int ret = 0;
  while (x) {
    ret = add(ret, c[x]);
    x -= x & -x;
  }
  return ret;
}
 
void inc(int x, int v) {
  while (x <= n) {
    c[x] = add(c[x], v);
    x += x & -x;
  }
}
void dec(int x, int v) {
  while (x <= n) {
    c[x] = del(c[x], v);
    x += x & -x;
  }
}
 
 
void solve() {
  n = rd(), mod = rd();
  inc(1, 1);
  dec(2, 1);
  FOR(i, 1, n + 1) {
    int cur = get(i);
    inc(i + 1, cur);
    for (int j = 2; j * i <= n; ++j) {
      inc(i * j, cur);
      dec(i * j + j, cur);
    }
  }
  cout << get(n) << '\n';
}
 
int main() {
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}
 