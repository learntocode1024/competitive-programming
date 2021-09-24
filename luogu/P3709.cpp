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
const int N = 200005;
const int B = 450;
int n, m;
int a[N], disc[N];

struct qry {
  int l, r, id;
  inline void init(int _i) {
    l = rd(), r = rd();
    id = _i;
  }
  bool operator< (const qry &rhs) const {
    return l / B == rhs.l / B ? r < rhs.r : l < rhs.l;
  }
} q[N];
int ans[N];
int c[N], b[N], cnt;
int tot;

void mov(int p, int t) {
  --c[b[a[p]]];
  if (t == 1) {
    if (cnt == b[a[p]]) ++cnt;
    ++b[a[p]];
    ++c[b[a[p]]];
  } else {
    if (cnt == b[a[p]] && c[b[a[p]]] == 0) --cnt;
    --b[a[p]];
    ++c[b[a[p]]];
  }
}

void solve() {
  n = rd(), m = rd();
  FOR(i, 1, n + 1) a[i] = disc[i-1] = rd();
  sort(disc, disc + n);
  tot = unique(disc, disc + n) - disc;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(disc, disc + tot, a[i]) - disc + 1;
  }
  c[0] = tot;
  FOR(i, 0, m) q[i].init(i);
  sort(q, q + m);
  int l = 0, r = 0;
  FOR(i, 0, m) {
    while (l > q[i].l) mov(--l, 1);
    while (r < q[i].r) mov(++r, 1);
    while (l < q[i].l) mov(l++, -1);
    while (r > q[i].r) mov(r--, -1);
    ans[q[i].id] = cnt;
  }
  FOR(i, 0, m) cout << -ans[i] << '\n';
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

