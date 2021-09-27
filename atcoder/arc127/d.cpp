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
// #define MULTI
const int N = 2.5e5 + 5;
int a[N], b[N];
i64 ans = 0;
using vi = vector<int>;
i64 cnt[20];
inline void count(int *a, const vi &x, const vi &y) {
  FOR(i, 0, 18) cnt[i] = 0;
  i64 n = x.size();
  for (auto s : x) {
    FOR(i, 0, 18) cnt[i] += (a[s] >> i) & 1;
  }
  for (auto t : y) {
    FOR(i, 0, 18) {
      if ((a[t] >> i) & 1) {
        ans += (n - cnt[i]) << i;
      } else
        ans += cnt[i] << i;
    }
  }
}

void solve(int i, vi s, vi t) {
  if (s.size() + t.size() < 2) return;
  if (i > 0) {
    vi s0, s1, t0, t1;
    for (auto v : s) {
      if (((a[v] ^ b[v]) >> (i - 1)) & 1) {
        s1.pb(v);
      } else
        s0.pb(v);
    }
    for (auto v : t) {
      if (((a[v] ^ b[v]) >> (i - 1)) & 1) {
        t1.pb(v);
      } else
        t0.pb(v);
    }
    solve(i - 1, s0, s1);
    solve(i - 1, t0, t1);
  } else {
    i64 reg = ans;
    count(a, s, s);
    count(a, t, t);
    ans = (ans + reg) >> 1;
  }
  vi a0, a1, b0, b1;
  for (auto v : s) {
    if (((a[v]) >> (i)) & 1) {
      a1.pb(v);
    } else
      a0.pb(v);
  }
  for (auto v : t) {
    if (((a[v]) >> (i)) & 1) {
      b1.pb(v);
    } else
      b0.pb(v);
  }
  count(a, a0, b0);
  count(b, a0, b1);
  count(a, a1, b1);
  count(b, a1, b0);
}

void solve() {
  int n = rd();
  FOR(i, 0, n) a[i] = rd();
  FOR(i, 0, n) b[i] = rd();
  vi s, t;
  FOR(i, 0, n) s.pb(i);
  solve(18, s, t);
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
