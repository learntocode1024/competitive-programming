/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 15, 2021
 * Algorithm: two-pointers
 * Difficulty: hard
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
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 100000

LL m;
int n;
struct pt {
  LL y, x;
  pt() {};
  pt(LL a, LL b) : y(a), x(b) {};
  bool operator<(const pt &b) const { return y < b.y || y == b.y && y < b.y; }
  bool operator== (const pt &b) const {
    return y == b.y && x == b.x;
  }
} a[MX], b[MX];

void chkmin(LL &a, LL b) { a = min(a, b); }

void chkmax(LL &a, LL b) { a = max(a, b); }

namespace SOL {
LL l[MX], r[MX];
LL query(pt *a, pt t) {
  LL ans = 0;
  if (*lower_bound(a, a + n, t) == t) return 0;
  int ls = lower_bound(a, a + n, pt(t.y, 0)) - a;
  l[ls] = 0, r[ls] = m;
  int p1;
  for (int i = ls - 1; i >= 0; --i) {
    l[i] = l[i + 1];
    r[i] = r[i + 1];
    if (i != ls - 1) {
      if (a[i + 1].x <= t.x) chkmax(l[i], a[i + 1].x);
      if (a[i + 1].x >= t.x) chkmin(r[i], a[i + 1].x);
    }
    if (r[i] - l[i] >= a[ls].y - a[i].y && l[i] < t.x && r[i] > t.x) p1 = i;
    else break;
  }
  for (int i = ls + 1; i < n; ++i) {
    l[i] = l[i - 1];
    r[i] = r[i - 1];
    if (a[i - 1].x <= t.x) chkmax(l[i], a[i - 1].x);
    if (a[i - 1].x >= t.x) chkmin(r[i], a[i - 1].x);
  }
  int p2 = ls;
  while (p2 < n) {
    while (min(r[p1], r[p2]) - max(l[p1], l[p2]) < a[p2].y - a[p1].y) ++p1;
    if (p1 >= ls && l[p2] == r[p2]) break;
    if (a[p1].y < t.y && a[p2].y > t.y) ans = max(ans, min(min(r[p1], r[p2]) - max(l[p1], l[p2]),a[p2].y - a[p1].y));
    // while(a[p2].y == a[p2 + 1].y)++p2;
    ++p2;
  }
  return ans;
} 

void solve() {
  sort(a, a + n);
  unique(a, a + n);
  sort(b, b + n);
  n = unique(b, b + n) - b;
  int q;
  scanf("%d", &q);
  while (q--) {
    pt t;
    scanf("%lld %lld", &t.x, &t.y);
    LL ans;
    if (t.x == 0 || t.y == 0 || t.x == m || t.y == m) ans = 0;
    else {ans = query(a, t);
    swap(t.y, t.x);
    chkmax(ans, query(b, t));}
    printf("%lld\n", ans * ans);
  }
}

} // namespace SOL

void solve() {
  scanf("%lld%d", &m, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &a[i].x, &a[i].y);
    b[i].y = a[i].x, b[i].x = a[i].y;
  }
  a[n].y = m;
  b[n].y = m;
  ++n;
  a[n].y = 0;
  b[n].y = 0;
  ++n;
  SOL::solve();
}

int main() {
  int T = 1;
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}
