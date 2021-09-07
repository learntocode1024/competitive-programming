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
const int N = 10000005;
i64 a[N];
i64 c[N];
int n;

void build() {
  for (int i = 1; i <= n; ++i) c[i] = a[i];
  for (int i = 1; i <= n; ++i) {
    int to = i + (i & -i);
    if (to <= n) c[to] += c[i];
  }
}

void change(int x, i64 v) {
  while (x <= n) {
    c[x] += v;
    x += x & -x;
  }
}

int get(int x) {
  i64 ret = 0;
  while (x) {
    ret += c[x];
    x -= x & -x;
  }
  return ret;
}

void query() {
  int l = 1, r = n + 1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (get(mid) >= 0) r = mid;
    else l = mid + 1;
  }
  cout << ((l <= n && get(l) == 0) ? "YES" : "NO") << '\n';
}

void solve() {
  int k = rd() - 1;
  n = rd();
  for (int i = 1; i <= n; ++i) a[i] = rd() - i;
  for (int i = n; i > 1; --i) a[i] -= a[i - 1];
  build();
  query();
  while (k--) {
    int l = rd(), r = rd(), c = rd();
    change(l, c);
    change(r + 1, -c);
    query();
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
