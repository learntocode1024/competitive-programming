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

const int N = 105, M = 1e5+5;
int n, m, q;
i64 a[N], b[M], db[M];
i64 ans;

struct segT {
  struct node {
    i64 s, tg, mx;
  } a[M<<2];
  inline void up(int p) {
    a[p].s = a[p<<1].s + a[p<<1|1].s;
    a[p].mx = max(a[p<<1].mx, a[p<<1|1].mx);
  }
  inline void upd(int p, int l, i64 v) {
    a[p].s += l * v;
    a[p].tg += v;
    a[p].mx += v;
  }
  inline void down(int p, int l, int r) {
    if (!a[p].tg) return;
    int mid = (l + r) / 2;
    upd(p<<1, mid - l, a[p].tg);
    upd(p<<1|1, r - mid, a[p].tg);
    a[p].tg = 0;
  }
  void build(int p = 1, int l = 1, int r = m) {
    if (r - l == 1) {
      a[p] = {db[l], 0, db[l]};
      return;
    }
    int mid = (l + r) / 2;
    build(p<<1, l, mid);
    build(p<<1|1, mid, r);
    up(p);
  }
  void add(int p, int l, int r, int s, int t, i64 v) {
    if (l == s && r == t) {
      return upd(p, r - l, v);
    }
    down(p, l, r);
    int mid = (l + r) / 2;
    if (s < mid) add(p<<1, l, mid, s, min(t, mid), v);
    if (t > mid) add(p<<1|1, mid, r, max(s, mid), t, v);
    up(p);
  }
  i64 calc(int p, int l, int r, i64 v) {
    if (r - l == 1) {
      if (a[p].s >= v) return 0;
      return v - a[p].s;
    }
    if (a[p].mx <= v) {
      return v * (r - l) - a[p].s;
    }
    down(p, l, r);
    int mid = (l + r) / 2;
    if (a[p<<1].mx >= v) return calc(p<<1, l, mid, v);
    return calc(p<<1, l, mid, v) + calc(p<<1|1, mid, r, v);
  }
} T;
i64 sa, sb, b1;

inline void solve() {
  rd(n, m, q);
  FOR(i, 1, n + 1) cin >> a[i], sa += a[i];
  FOR(i, 1, m + 1) cin >> b[i], sb += b[i];
  FOR(i, 1, m) db[i] = b[i + 1] - b[i];
  T.build();
  b1 = b[1];
  ans = sa + sb + a[n] * (m - 1) + b1 * (n - 1);
  while (q--) {
    int t, k, d;
    rd(t, k, d);
    if (t == 1) {
      FOR(i, n - k + 1, n + 1) a[i] += 1ll * (i - n + k) * d;
      sa += 1ll * d * k * (k + 1) / 2;
    } else {
      sb += 1ll * d * k * (k + 1) / 2;
      if (k == m) {
        --k;
        b1 += d;
      }
      T.add(1, 1, m, m - k, m, d);
    }
    i64 cur = 0;
    ans = sa + sb + a[n] * (m - 1) + b1 * (n - 1);
    FOR(i, 1, n) cur += T.calc(1, 1, m, a[i + 1] - a[i]);
    cout << ans - cur << '\n';
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

