/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 21, 2021
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

/********************************* macros *************************************/
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
#define pb(x) push_back(x)
#define fi first
#define se second
#define REP(x, y, z) for (int x = y; x < z; ++x) // always [y, z)
#define PER(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T> void chkmax(T &a, const T &b) { a = max(a, b); }
template <typename T> void chkmin(T &a, const T &b) { b = min(a, b); }

/*********************************** solution *********************************/
#define MX 100005
int a[MX], blk[MX];
int n, m, k;
int B = 350;
struct qry {
  int l, r, id;
  i64 ans;
  qry() {};
  qry(int a, int b, int c) : l(a), r(b), id(c), tg(0) {};
  bool operator<(const qry &b) const {
    return (blk[l] == blk[b.l]) ? r < b.r : l < b.l;
  }
  bool tg;
  inline void rd(int i) {
    cin >> l >> r;
    id = i;
  }
} q[MX];

i64 p[MX], pp[MX];
int b[MX], tot;

int c[MX];
int get(int x) {
  int ret = 0;
  while (x) {
    ret += c[x];
    x -= x & -x;
  }
  return ret;
}
void inc(int x) {
  while (x <= n) {
    ++c[x];
    x += x & -x;
  }
}

vector<qry> sq[MX];
i64 res[MX];
i64 in[MX], cr[MX];
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i - 1] = a[i];
    blk[i] = blk[i - 1] + (i % B == 1);
  }
  sort(b, b + n);
  tot = unique(b, b + n) - b;
  for (int i = 1; i <= n; ++i) {
    a[i] = lower_bound(b, b + tot, a[i]) - b + 1;
  }
  for (int i = 1; i <= m; ++i) q[i].rd(i);
  for (int i = 1; i <= n; ++i) {
    p[i] = get(n) - get(a[i]);
    pp[i] = get(a[i] - 1);
    inc(a[i]);
  }
  sort(q + 1, q + m + 1);
  
  int l = 1, r = 1;
  for (int i = 1; i <= m; ++i) {
    if (r < q[i].r) sq[l - 1].emplace_back(r + 1, q[i].r, -i);
    while (r < q[i].r) {
      ++r;
      q[i].ans += p[r];
    }
    if (l > q[i].l) sq[r].emplace_back(q[i].l, l - 1, i), sq[r].back().tg = 1;
    while (l > q[i].l) {
      --l;
      q[i].ans -= pp[l];
    }
    if (r > q[i].r) sq[l - 1].emplace_back(q[i].r + 1, r, i);
    while (r > q[i].r) {
      q[i].ans -= p[r];
      --r;
    }
    if (l < q[i].l) sq[r].emplace_back(l, q[i].l - 1, -i), sq[r].back().tg = 1;
    while (l < q[i].l) {
      q[i].ans += pp[l];
      ++l;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = blk[a[i]]; j <= blk[n]; ++j) ++ cr[j];
    for (int j = a[i]; blk[j] == blk[a[i]]; ++j) ++in[j];
    for (auto s : sq[i]) {
      for (int j = s.l; j <= s.r; ++j) {
        i64 cur = cr[blk[n]] - cr[blk[a[j]] - 1] - in[a[j]];
        if (s.tg) cur = cr[blk[a[j]] - 1] + in[a[j] - 1] * (blk[a[j]] == blk[a[j] - 1]);
        if (s.id < 0) q[-s.id].ans -= cur;
        else q[s.id].ans += cur;
      }
    }
  }
  for (int i = 2; i <= m; ++i) q[i].ans += q[i - 1].ans;
  for (int i = 1; i <= m; ++i) res[q[i].id] = q[i].ans;
  for (int i = 1; i <= m; ++i) cout << res[i] << '\n';
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
  return 0;
}
