/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
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
const int N = 5005;
int n;
char s[N];
i64 h[N], pw[N];
const i64 k = 1145141;
// const i64 p = 2869404841;
int dp[N];
int A, B;
inline void Hash() {
  h[0] = s[0];
  pw[0] = 1;
  FOR(i, 1, n) {
    h[i] = 1ll * h[i - 1] * k + s[i];
    pw[i] = 1ll * pw[i - 1] * k;
  }
}

inline i64 H(int l, int r) {
  --r, --l;
  i64 ret = h[r];
  if (l) ret = ret - 1ll * h[l - 1] * pw[r - l + 1];
  return ret;
}

i64 e[N * N], tot;
int hs[N][N];
i64 ha[N][N];
int g[N * N];

void solve() {
  n = rd(), A = rd(), B = rd();
  IO::rdstr(s);
  Hash();
  FOR(i, 1, n) FOR(j, i, n + 1) {
    ha[i][j] = H(i, j);
    e[tot++] = ha[i][j];
  }
  sort(e, e + tot);
  tot = unique(e, e + tot) - e;
  FOR(i, 1, n) FOR(j, i, n + 1) {
    hs[i][j] = lower_bound(e, e + tot, ha[i][j]) - e;
  }
  FOR(i, 1, n) FOR(j, i, n + 1) {
    if (g[hs[i][j]] == 0) g[hs[i][j]] = j;
    else chkmin(g[hs[i][j]], j);
  }
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i - 1] + A;
    for (int j = i; j > 0; --j) {
      if (g[hs[i][j]] < j) {
        chkmin(dp[i], dp[j - 1] + B);
      }
    }
  }
  cout << dp[n] << '\n';
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
