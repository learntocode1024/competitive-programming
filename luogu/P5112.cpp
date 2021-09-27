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
char in[1 << 26];  // sizeof in varied in problem
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
const int N = 3e6 + 5, M = 1e5 + 5;
int n, m, k;
char s[N];
u64 H[N];
int blk[N];
const int B = 1000;
struct qry {
  int l, r, id;
  qry() = default;
  qry(int _l, int _r, int _id) : l(_l), r(_r), id(_id){};
  bool operator<(const qry &b) const {
    return (blk[l] ^ blk[b.l]) ? l < b.l : (r < b.r);
  }
} q[N];

u64 srt[N], aa[N];
int a[N];

void Hash() {
  H[1] = s[1];
  const u64 b = 131;
  FOR(i, 2, n + 1) { H[i] = H[i - 1] * b + s[i]; }
  u64 pwk = b;
  FOR(i, 1, k) pwk *= b;
  FOR(i, 1, n + 2 - k) { srt[i - 1] = aa[i] = H[i + k - 1] - H[i - 1] * pwk; }
  sort(srt, srt + n - k + 1);
  int ss = unique(srt, srt + n - k + 1) - srt;
  FOR(i, 1, n - k + 2) { a[i] = lower_bound(srt, srt + ss, aa[i]) - srt + 1; }
}

i64 cnt;
i64 ans[M];
int c[N];

void solve() {
  n = rd(), m = rd(), k = rd();
  IO::rdstr(s + 1);
  int tot = 0;
  for (int i = 1; i <= n; ++i) {
    blk[i] = (i - 1) / B + 1;
  }
  FOR(i, 0, m) {
    int l = rd(), r = rd();
    chkmin(r, n - k + 1);
    if (l > r) l = 1, r = 0;
    q[i] = qry(l, r, i);
  }
  sort(q, q + m);
  Hash();
  int l = 1, r = 0;
  FOR(i, 0, m) {
    while (r < q[i].r) cnt += c[a[++r]]++;
    while (l > q[i].l) cnt += c[a[--l]]++;
    while (l < q[i].l) cnt -= --c[a[l++]];
    while (r > q[i].r) cnt -= --c[a[r--]];
    ans[q[i].id] = cnt;
  }
  FOR(i, 0, m) { cout << ans[i] << '\n'; }
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
