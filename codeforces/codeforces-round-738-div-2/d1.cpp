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
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/********************************** buffer IO *********************************/
namespace IO {
char in[1 << 24];  // sizeof in varied in problem
char const *o;
void init_in() {
  o = in;
  in[fread(in, 1, sizeof(in) - 4, stdin)] = 0;  // set 0 at the end of buffer.
}
int rd() {
  unsigned u = 0, s = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-')
    s = ~s, ++o;
  else if (*o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = (u << 3) + (u << 1) + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return static_cast<int>((u ^ s) + !!s);
}
char *rdstr(char *s) {
  while (*o && *o <= 32) ++o;
  while (*o > 32) *s++ = *o++;
  return s;
}
}  // namespace IO

/********************************* utility ************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}

/*********************************** solution *********************************/
using IO::rd;
#define MX 10005

int f1[MX], f2[MX];

int get(int *f, int x) {
  if (x == f[x]) return x;
  f[x] = get(f, f[x]);
  return f[x];
}

void solve() {
  int n = rd(), m1 = rd(), m2 = rd();
  FOR(i, 1, n) f1[i] = f2[i] = i;
  FOR(i, 0, m1) {
    int a = rd(), b = rd();
    if (get(f1, a) != get(f1, b)) {
      f1[get(f1, a)] = get(f1, b);
    }
  }
  FOR(i, 0, m2) {
    int a = rd(), b = rd();
    if (get(f2, a) != get(f2, b)) {
      f2[get(f2, a)] = get(f2, b);
    }
  }
  int cnt =  n - 1 - max(m1, m2);
  cout << n - 1 - max(m1, m2) << '\n';
  for (int u = 1; u <= n; ++u) {
    for (int v = u + 1; v <= n; ++v) {
      if (!cnt) return;
      if (get(f1, u) != get(f1, v) && get(f2, u) != get(f2, v)) {
        --cnt;
        cout << u << ' ' << v << '\n';
        f1[get(f1, u)] = get(f1, v);
        f2[get(f2, u)] = get(f2, v);
      }
    }
  }
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

