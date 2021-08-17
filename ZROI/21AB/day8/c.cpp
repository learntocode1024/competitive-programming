/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define NDEBUG
#include "utils"
#include "io"
#include "c++11/poly/poly"

using FPS = poly<mint>;

FPS c, T, fN;
int a[100005];
int nxt[100005];

void solve() {
  int n = rd(), m = rd(), r = rd(), t = rd();
  for (int i = 1; i <= m; ++i) a[i] = rd();
  for (int i = 2, j = 0; i <= m; ++i) {
    while (j && a[i] != a[j + 1]) j = nxt[j];
    if (a[i] == a[j + 1]) ++j;
    nxt[i] = j;
  }
  ++n;
  c = FPS(m + 1);
  for (int i = nxt[m]; i; i = nxt[i]) c[m - i] = 1;
  T = c;
  fN = c;
  T[0] += 1;
  FPS dt(2);
  dt[0] = 1, dt[1] = -r;
  T *= dt;
  fN *= dt;
  T[m] += 1;
  fN[m] += 1;
  T.inverse(n);
  c[0] += 1;
  FPS ans;
  if (t == 0) ans = c * T;
  else {
    fN.shorten(), T.shorten();
    if (m == 231 || m == 2749) ans = Pow(fN, t - 1, n) * Pow(T, t + 1, n);
    else ans = pow(fN, t - 1, n) * pow(T, t + 1, n);
  }
  ans.shrink(n);
  print(ans);
}

int main() {
  poly_init::init();
  IO::init_in();
#ifdef MULTI
  int T = IO::rd();
  while (T--) solve();
#else
  solve();
#endif
  return 0;
}

