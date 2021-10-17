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
#define MULTI
const int N = 1e5+5;
i64 d[N << 1];
i64 l[N], r[N];
int c[N << 1], cc[N << 1];
i64 cnt[N];

void solve() {
  int n;
  i64 m;
  int tot = 0;
  cin >> n >> m;
  FOR(i, 0, n) {
    cin >> l[i] >> r[i];
    d[tot] = l[i];
    d[tot + 1] = r[i];
    tot += 2;
  }
  FOR(i, 0, n + 1) cnt[i] = 0;
  sort(d, d + tot);
  tot = unique(d, d + tot) - d;
  FOR(i, 0, tot) c[i] = cc[i] = 0;
  FOR(i, 0, n) {
    l[i] = lower_bound(d, d + tot, l[i]) - d;
    r[i] = lower_bound(d, d + tot, r[i]) - d;
    ++c[r[i]];
    --c[l[i]];
    ++cc[r[i]];
  }
  ROF(i, 0, tot - 1) c[i] += c[i + 1];
  FOR(i, 1, tot) {
    cnt[c[i]] += d[i] - d[i - 1] - 1;
    ++cnt[c[i] - cc[i]];
  }
  i64 ans = n;
  for (int i = n; i > 0; --i) {
    if (!m) break;
    i64 cur = min(m, cnt[i]);
    ans += i * cur;
    m -= cur;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
#ifdef MULTI
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ": ";
    solve();
  }
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
