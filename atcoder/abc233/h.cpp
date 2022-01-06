#include <bits/stdc++.h>
using namespace std;
template<typename T>
void rd(T &a) {
  cin >> a;
}
template<typename A, typename... B>
void rd(A &a, B& ...b) {
  cin >> a;
  rd(b...);
}
template<typename A>
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

const int N = 2e5+5, S = 1e5;
int n, q;
pii c[N];
int rt[N];
struct node {
  int l, r;
  int c;
} a[N<<5];
int tot;

inline int cpy(int p) {
  int ret = ++tot;
  a[ret] = a[p];
  return ret;
}

int upd(int p, int l, int r, int k) {
  p = cpy(p);
  ++a[p].c;
  if (r - l == 1) {
    return p;
  }
  int mid = (l + r) >> 1;
  if (k < mid) a[p].l = upd(a[p].l, l, mid, k);
  else a[p].r = upd(a[p].r, mid, r, k);
  return p;
}

int get(int p, int l, int r, int s, int t) {
  if (!p) return 0;
  if (l == s && r == t) {
    return a[p].c;
  }
  int mid = (l + r) >> 1;
  int ret = 0;
  if (s < mid) ret += get(a[p].l, l, mid, s, min(mid, t));
  if (t > mid) ret += get(a[p].r, mid, r, max(mid, s), t);
  return ret;
}

inline int cnt(int x, int y, int r) {
  int rr = lower_bound(c, c + n, mkp(x + r + 1, 0)) - c;
  int lr = lower_bound(c, c + n, mkp(x - r, 0)) - c;
  return get(rt[rr], 0, S<<1|1, max(0, y - r), min(S<<1|1, y + r + 1))
    - get(rt[lr], 0, S<<1|1, max(0, y - r), min(S<<1|1, y + r + 1));
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) {
    int x, y;
    rd(x, y);
    c[i] = {x - y + S, x + y};
  }
  sort(c, c + n);
  FOR(i, 0, n) {
    rt[i + 1] = upd(rt[i], 0, S<<1|1, c[i].se);
  }
  cin >> q;
  FOR(i, 0, q) {
    int x, y, k, t;
    rd(x, y, k);
    t = x;
    x = t - y + S;
    y = t + y;
    if (cnt(x, y, 0) >= k) {
      println(0);
      continue;
    }
    int l = 0, r = 2 * S;
    while (r - l > 1) {
      int mid = (l + r) >> 1;
      if (cnt(x, y, mid) >= k) r = mid;
      else l = mid;
    }
    println(r);
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
  solve();
  return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */

