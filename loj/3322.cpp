/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm: heap, k-th-min(heap)
 * Difficulty: hard
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 200005

const LL inf = 0x3f3f3f3f3f3f3f3f;

int n, m, k;

struct grp {
  int l, r;
  vector<LL> a, s;
  struct stat {
    int l, p, r;
    LL val;
    stat(int a, int b, int c, LL d) : l(a), p(b), r(c), val(d){};
    bool operator<(const stat &b) const { return val < b.val; };
  };
  priority_queue<stat> pq;
  void init() {
    sort(begin(a), end(a));
    if (l > a.size()) {
      while (k--) puts("-1");
      exit(0);
    }
    if (r > a.size())
      r = a.size();
    LL s0 = 0;
    if (!l) s.push_back(0);
    for (int i = 0; i < r; ++i) {
      s0 += a[i];
      if (i >= l - 1) pq.push(stat(i, i, a.size(), -s0));
    }
  }
  LL operator[](unsigned k) {
    while (!pq.empty() && s.size() < k) {
      auto t = pq.top();
      pq.pop();
      s.push_back(-t.val);
      if (t.p + 1 < t.r) {
        pq.push(stat(t.l, t.p + 1, t.r, t.val - a[t.p + 1] + a[t.p]));
      }
      if (t.l && t.p > t.l) {
        pq.push(stat(t.l - 1, t.l, t.p, t.val - a[t.l] + a[t.l - 1]));
      }
    }
    if (k > s.size())
      return inf;
    return s[k - 1];
  }
  LL diff() {
    if ((*this)[1] == inf)
      return inf;
    return (*this)[2] - (*this)[1];
  }
} A[MX];

struct stat {
  int p, c;
  LL val;
  stat(int a, int b, LL d) : p(a), c(b), val(d){};
  bool operator<(const stat &b) const { return val < b.val; };
};

priority_queue<stat> pq;

void solve() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i) {
    int a, c;
    cin >> a >> c;
    --a;
    A[a].a.push_back(c);
  }
  for (int i = 0; i < m; ++i) {
    cin >> A[i].l >> A[i].r;
    A[i].init();
  }
  sort(A, A + m, [](auto a, auto b) { return a.diff() < b.diff(); });
  LL s0 = 0;
  for (int i = 0; i < m; ++i)
   s0 += A[i][1];
  cout << s0 << endl;--k;
  if (A[0][2] != inf) pq.push(stat(0, 2, -s0 - A[0].diff()));
  while (!pq.empty() && k--) {
    auto t = pq.top();
    LL val = t.val;
    int p = t.p, c = t.c;
    pq.pop();
    cout << -val << endl;
    if (A[p][c + 1] != inf) {
      pq.push(stat(p, c + 1, val - A[p][c + 1] + A[p][c]));
    }
    if (c == 2 && p + 1 < m && A[p + 1][2] != inf) {
      pq.push(stat(p + 1, 2, val + A[p].diff() - A[p + 1].diff()));
    }
    if (p + 1 < m && A[p + 1][2] != inf) {
      pq.push(stat(p + 1, 2, val - A[p + 1].diff()));
    }
  }
  while (k-- > 0)
    puts("-1");
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}
