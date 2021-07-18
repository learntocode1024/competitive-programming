/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 17, 2021
 * Algorithm: segment-tree, 2D-point-sum
 * Difficulty: mid
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
#define MX 1000005

template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  b = min(a, b);
}

namespace SEGTREE {
typedef pair<int, int> id;
id v[MX << 2];
id tg[MX << 2];
const id nil = make_pair(0, 0);
void pushdown(int p) {
  if (tg[p] == nil) return;
  int lc = p << 1, rc = lc + 1;
  tg[rc] = tg[lc] = v[rc] = v[lc] = tg[p];
  tg[p] = nil;
}
void assign(int p, int l, int r, int s, int t, id val) {
  if (l == s && r == t) {
    v[p] = val;
    tg[p] = val;
    return;
  }
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  pushdown(p);
  if (s < mid) assign(lc, l, mid, s, min(mid, t), val);
  if (t > mid) assign(rc, mid, r, max(s, mid), t, val);
}

id get(int p, int l, int r, int pos) {
  if (r - l == 1) return v[p];
  int mid = l + (r - l) / 2;
  int lc = p << 1, rc = lc + 1;
  pushdown(p);
  if (pos < mid) return get(lc, l, mid, pos);
  else return get(rc, mid, r, pos);
}
}
int n, m, q;
int ops[MX][4];

namespace SUBTASK1 {
inline void solve() {
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    LL ans = 0;
    for (int i = l; i <= r; ++i) {
      if (ops[i][0] == 1) {
        pair<int, int> px = SEGTREE::get(1, 0, n, ops[i][1] - 1);
        pair<int, int> py = SEGTREE::get(1, 0, n, ops[i][2] - 1);
        px.second = 114514, py.second = 114514;
        SEGTREE::assign(1, 0, n, ops[i][1] - 1, ops[i][1], py);
        SEGTREE::assign(1, 0, n, ops[i][2] - 1, ops[i][2], px);
      } else if (ops[i][0] == 2) {
        SEGTREE::assign(1, 0, n, ops[i][1] - 1, ops[i][2], make_pair(ops[i][3], 114514));
      } else {
        ans += SEGTREE::get(1, 0, n, ops[i][1] - 1).first;
      }
    }
    printf("%lld\n", ans);
    SEGTREE::assign(1, 0, n, 0, n, make_pair(0, 114514));
  }
}
}

namespace SUBTASK3 {
LL bt[MX];
LL ans[MX];
pair<int, int> vl[MX];
struct query {
  int l, r, t;
  bool operator< (const query &b) const {
    return r < b.r;
  }
} c[MX];
void insert(int x, LL v) {
  while (x <= m) {
    bt[x] += v;
    x += x & -x;
  }
}
LL get(int x) {
  LL ret = 0;
  while (x) {
    ret += bt[x];
    x -= x & -x;
  }
  return ret;
}

inline void solve() {
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", &c[i].l, &c[i].r);
    c[i].t = i;
  }
  sort(c, c + q);
  for (int i = 1; i <= m; ++i) {
    if (ops[i][0] == 2) {
      SEGTREE::assign(1, 0, n, ops[i][1] - 1, ops[i][2], make_pair(ops[i][3], i));
    } else {
      vl[i] = SEGTREE::get(1, 0, n, ops[i][1] - 1);
    }
  }
  int curr = 0;
  pair<int, int> nil = make_pair(0, 0);
  for (int i = 1; i <= m; ++i) {
    if (vl[i] != nil) {
      insert(vl[i].second, vl[i].first);
    }
    while (c[curr].r == i) {
      ans[c[curr].t] = get(c[curr].r) - get(c[curr].l - 1);
      ++curr;
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ans[i]);
  }
}
}

namespace SUBTASK4 {
inline void solve() {
  while (q--) {
    puts("0");
  }
}
}
namespace SOL {
LL bt[MX];
LL ans[MX];
pair<int, int> vl[MX];
struct query {
  int l, r, t;
  bool operator< (const query &b) const {
    return r < b.r;
  }
} c[MX];
void insert(int x, LL v) {
  while (x <= m) {
    bt[x] += v;
    x += x & -x;
  }
}
LL get(int x) {
  LL ret = 0;
  while (x) {
    ret += bt[x];
    x -= x & -x;
  }
  return ret;
}

inline void solve() {
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", &c[i].l, &c[i].r);
    c[i].t = i;
  }
  sort(c, c + q);
  for (int i = 1; i <= m; ++i) {
    if (ops[i][0] == 1) {
      pair<int, int> p1 = SEGTREE::get(1, 0, n, ops[i][1] - 1);
      pair<int, int> p2 = SEGTREE::get(1, 0, n, ops[i][2] - 1);
      // p1.second = p2.second = i;
      SEGTREE::assign(1, 0, n, ops[i][1] - 1, ops[i][1], p2);
      SEGTREE::assign(1, 0, n, ops[i][2] - 1, ops[i][2], p1);
    } else if (ops[i][0] == 2) {
      SEGTREE::assign(1, 0, n, ops[i][1] - 1, ops[i][2], make_pair(ops[i][3], i));
    } else {
      vl[i] = SEGTREE::get(1, 0, n, ops[i][1] - 1);
    }
  }
  int curr = 0;
  pair<int, int> nil = make_pair(0, 0);
  for (int i = 1; i <= m; ++i) {
    if (vl[i] != nil) {
      insert(vl[i].second, vl[i].first);
    }
    while (c[curr].r == i) {
      ans[c[curr].t] = get(c[curr].r) - get(c[curr].l - 1);
      ++curr;
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ans[i]);
  }
}
}
void solve() {
  bool prop1(1), prop2(1);
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", ops[i]);
    switch (ops[i][0]) {
      case 1:
      prop1 = 0;
      scanf("%d%d", ops[i] + 1, ops[i] + 2);
      continue;
      case 2:
      prop2 = 0;
      scanf("%d%d%d", ops[i] + 1, ops[i] + 2, ops[i] + 3);
      continue;
      default:
      scanf("%d", ops[i] + 1);
    }
  }
  SOL::solve();
  return;
  /* for (int i = 0; i < q; ++i) { */
  /*   scanf("%d%d", query[i], query[i] + 1); */
  /* } */
  if (n <= 1000 && m <= 1000 && q <= 1000) SUBTASK1::solve();
  else if (prop1) SUBTASK3::solve();
  else if (prop2) SUBTASK4::solve();
  else SOL::solve();
}

int main() {
  solve();
  return 0;
}
