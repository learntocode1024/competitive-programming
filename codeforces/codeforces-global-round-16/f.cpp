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
const int N = 200005;
int n, m;
i64 a[N];
i64 dp[2][N];
vector<pii> q[N];
map<int, int> ss;

void solve() {
  ss.clear();
  int n = rd(), m = rd();
  FOR(i, 0, n + 2) q[i].clear();
  ss.insert(mkp(-1000000007, 0));
  ss.insert(mkp(1000000007, 0));
  FOR(i, 1, n + 1) a[i] = rd(), ss.insert(mkp(a[i], 0));
  int tot = 0;
  for (auto i = ss.begin(); i != ss.end(); ++i) {
    i->se = tot++;
  }
  FOR(i, 0, m) {
    int l = rd(), r = rd();
    auto it = ss.lower_bound(l);
    if ((*it).fi <= r) continue;
    q[(*it).se].emplace_back(l, r);
  }
  sort(a + 1, a + n + 1);
  a[0] = -1e14;
  a[n+1] = 1e14;
  dp[0][0] = 0;
  dp[1][0] = 1e15;
  FOR(i, 1, n + 2) {
    dp[1][i] = dp[0][i] = 1e18;
    i64 lc = 0, rc = 0;
    sort(q[i].begin(), q[i].end());
    i64 mn = a[i];
    for (int j = q[i].size() - 1; j >= 0; --j) {
      if (j + 1 == q[i].size() || q[i][j].fi <= q[i][j + 1].fi) {
        lc = q[i][j].fi - a[i - 1];
        rc = a[i] - mn;
        chkmin(dp[0][i], min(dp[0][i - 1] + 2*lc+rc, dp[1][i - 1] + lc+rc));
        chkmin(dp[1][i], min(dp[0][i - 1] + 2*lc+2*rc, dp[1][i - 1] + lc+2*rc));
      }
      chkmin(mn, 1ll * q[i][j].se);
    }
    if (q[i].empty()) {
      dp[1][i] = min(dp[0][i - 1], dp[1][i - 1]);
    } else {
      rc = a[i] - mn;
      chkmin(dp[0][i], min(dp[0][i - 1] + rc, dp[1][i - 1] + rc));
      chkmin(dp[1][i], min(dp[0][i - 1] + 2*rc, dp[1][i - 1] + 2*rc));
    }
  }
  cout << min(dp[0][n+1], dp[1][n+1]) << '\n';
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
