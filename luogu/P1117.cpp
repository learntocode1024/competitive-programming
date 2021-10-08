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
  *s = '\0';
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
#define MULTI
const int N = 3e4+5;
char s[N];
i64 _h[N];
i64 pw[N];
const i64 g = 1145141;
const i64 p = 1e9+7;
int n;

inline void Hash() {
  pw[0] = 1;
  for (int i = 1; i < n; ++i) pw[i] = pw[i - 1] * g % p;
  _h[0] = s[0];
  for (int i = 1; i < n; ++i) _h[i] = (_h[i - 1] * g + s[i]) % p;
}

inline u64 h(int l, int r) { // [l, r]
  if (r < l) return 0;
  u64 ret = _h[r];
  if (l) ret += p - _h[l - 1] * pw[r - l + 1] % p;
  return ret % p;
}

int lcp(int x, int y) {
  if (x > y) swap(x, y);
  int l = 0, r = x + 2;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (h(x - mid + 1, x) == h(y - mid + 1, y)) l = mid;
    else r = mid;
  }
  return l;
}

int lcs(int x, int y) {
  if (x > y) swap(x, y);
  int l = 0, r = n - y + 1;
  while (r - l > 1) {
    int mid = (l + r) >> 1;
    if (h(x, x + mid - 1) == h(y, y + mid - 1)) l = mid;
    else r = mid;
  }
  return l;
}


int f[N], ff[N];

void solve() {
  n = IO::rdstr(s) - s;
  for (int i = 0; i < n; ++i) f[i] = ff[i] = 0;
  Hash();
  for (int k = 1; k < n; ++k) {
    for (int i = 0; (i + 1) * k <= n; ++i) {
      int l = i * k - lcp(i * k, (i + 1) * k) + 1, r = (i + 1) * k + lcs(i * k, (i + 1) * k);
      chkmax(l, (i - 1) * k + 1);
      chkmin(r, (i + 2) * k);
      if (r - l >= 2 * k) {
        ++ff[l];
        --ff[r - 2 * k + 1];
        ++f[l + 2 * k - 1];
        --f[r];
      }
    }
  }
  for (int i = 1; i < n; ++i) f[i] += f[i - 1], ff[i] += ff[i - 1];
  i64 ans = 0;
  for (int i = 1; i < n - 1; ++i) ans += 1ll * f[i] * ff[i + 1];
  cout << ans << '\n';
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
/*
 * checklist:
 * - IO buffer size
 * - potential out-of-bound Errors
 * - inappropriate variable type
 * - potential Arithmetic Error
 * - potential Arithmetic Overflow
 * - typo / logical flaws
 * - clean-up on multiple test cases
 * - sufficient stress tests / random data tests
*/
