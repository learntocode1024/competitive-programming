/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 13, 2021
 * Source: ZROI simulation contests for NOI2021
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double FLOAT;
const LL mod = 1e9 + 7;
#define printb(x)                                                              \
  if ((bool)x)                                                                 \
    printf("YES");                                                             \
  else                                                                         \
    printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 200005

/*** */
namespace IO {
char in[1 << 21]; // sizeof in varied in problem
char const *o;

void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0; // set 0 at the end of buffer.
}

int readInt() {
  unsigned u = 0, s = 0;

  while (*o && *o <= 32)
    ++o; // skip whitespaces...

  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o; // skip sign

  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0'); // u * 10 = u * 8 + u * 2 :)

  return static_cast<int>((u ^ s) + !!s);
}
} // namespace IO
/* */

int n;
FLOAT x[MX], y[MX];

namespace BF1 {
void solve() {
  for (int i = 0; i < n; ++i) {
    FLOAT ans = 0;
    for (int j = 0; j < n; ++j) {
      FLOAT a = x[i] - x[j], b = y[i] - y[j];
      ans += sqrt((long double)(a * a + b * b));
    }
    printf("%.4Lf\n", ans);
  }
}
} // namespace BF1

namespace CORR {
const int iter = 39;
const FLOAT ang = 2 * M_PI / iter;
FLOAT a[MX];
pair<FLOAT, int> tmp[MX];
inline FLOAT dist(int i, int j) {
  FLOAT a = x[i] - x[j], b = y[i] - y[j];
  return sqrt((long double)(a * a + b * b));
}
void solve() {
  for (int I = 1; I <= iter; ++I) {
    FLOAT x0 = cos((long double)ang * I), y0 = sin((long double)ang * I);
    for (int i = 0; i < n; ++i) {
      tmp[i] = make_pair(x[i] * x0 + y[i] * y0, i);
    }
    sort(tmp, tmp + n);
    FLOAT s(0);
    for (int i = 0; i < n; ++i) {
      a[tmp[i].second] += i * tmp[i].first - s;
      s += tmp[i].first;
    }
    s = 0;
    for (int i = n - 1; i >= 0; --i) {
      a[tmp[i].second] += s - (n - i - 1) * tmp[i].first;
      s += tmp[i].first;
    }
  }
  FLOAT chk(0);
  for (int i = 1; i < n; ++i) {
    chk += dist(0, i);
  }
  FLOAT err = a[0] / chk;
  for (int i = 0; i < n; ++i) {
    printf("%.4Lf\n", a[i] / err);
  }
}
} // namespace CORR

void solve() {
  scanf("%d", &n);
  // n = IO::readInt();
  for (int i = 0; i < n; ++i) {
    // x[i] = IO::readInt();
    // y[i] = IO::readInt();
    scanf("%Lf %Lf", x + i, y + i);
  }
  if (n <= 3000) {
    BF1::solve();
  } else {
    CORR::solve();
  }
}

int main() {
  // IO::init_in();
  int T = 1;
  while (T--)
    solve();
  return 0;
}
