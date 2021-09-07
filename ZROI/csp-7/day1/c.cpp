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
#include <cmath>
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
const int N = 100005;
int blk[N];

int ans[N];
struct qry {
  int l, r, id;
  bool operator< (const qry& b) const {
    return blk[l] < blk[b.l] || (blk[l] == blk[b.l] && r < b.r);
  }
} q[N];

int a[N], dis[N];

int cnt, buc[N];

inline void ch(int x, int t) {
  buc[a[x]] += t;
  if (buc[a[x]] & 1) ++cnt;
  else --cnt;
}

void solve() {
  int n = rd();
  int B = sqrt(n) + 1;
  for (int i = 1; i <= n; ++i) {
    blk[i] = blk[i - 1];
    if (i % B == 1) ++blk[i];
  }
  for (int i = 0; i < n; ++i) {
    a[i + 1] = dis[i] = rd();
  }
  sort(dis, dis + n);
  int tot = unique(dis, dis + n) - dis;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(dis, dis + tot, a[i]) - dis;
  } // discrete
  int m = rd();
  for (int i = 0; i < m; ++i) {
    q[i].l = rd(), q[i].r = rd();
    q[i].id = i;
  }
  sort(q, q + m);
  int l = 1, r = 1;
  for (int i = 0; i < m; ++i) {
    while (l > q[i].l) ch(--l, 1);
    while (r <= q[i].r) ch(r++, 1);
    while (l < q[i].l) ch(l++, -1);
    while (r > q[i].r + 1) ch(--r, -1);
    ans[q[i].id] = cnt;
  }
  for (int i = 0; i < m; ++i) {
    cout << ans[i] << '\n';
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
