#include <bits/stdc++.h>
#include "modint"
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

#define MULTI
const int N = 2e5+5;
int n;
typedef MontgomeryModInt<1000000007> mint;
int a[N];
int dis[N];
mint f[N];
int NUM, NUM1;

struct BIT {
  mint c[N];
  int op[N];
  void add(int x, mint v) {
    for (; x <= n; x += x & -x) {
      if (op[x] != NUM) op[x] = NUM, c[x] = 0;
      c[x] += v;
    }
  }
  mint get(int x) {
    mint ret(0);
    for (; x; x -= x & -x) {
      if (op[x] != NUM) op[x] = NUM, c[x] = 0;
      ret += c[x];
    }
    return ret;
  }
} A, B, C;
struct BIT2 {
  mint c[N];
  int op[N];
  void add(int x, mint v) {
    for (; x <= n; x += x & -x) {
      if (op[x] != NUM1) op[x] = NUM1, c[x] = 0;
      c[x] += v;
    }
  }
  mint get(int x) {
    mint ret(0);
    for (; x; x -= x & -x) {
      if (op[x] != NUM1) op[x] = NUM1, c[x] = 0;
      ret += c[x];
    }
    return ret;
  }
} D;

int l[N], o[N], smx[N];

inline void get_f() {
  FOR(i, 1, n + 1) {
    mint cnt = A.get(a[i]-1) + 1;
    A.add(a[i], cnt);
    f[i] = cnt + B.get(a[i]-1);
    B.add(a[i], f[i]);
  }
}
int tx[N];
mint tv[N];
int tc;
inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) cin >> a[i];
  copy(a + 1, a + n + 1, dis);
  sort(dis, dis + n);
  int ttt = unique(dis, dis + n) - dis;
  FOR(i, 1, n + 1) a[i] = lower_bound(dis, dis + ttt, a[i]) - dis + 1;
  get_f();
  mint ans(0);
  int t = 0;
  l[0] = n;
  for (int i = n - 1; i >= 0 && a[l[t]] < ttt; --i) {
    if (a[i] > a[l[t]]) l[++t] = i;
  }
  iota(o, o + n, 1);
  sort(o, o + n, [] (int i, int j) { return a[i] == a[j] ? i < j : (a[i] > a[j]); });
  int t1 = 0, t2 = 0;
  while (t2 < n && a[o[t2]] == a[l[t]]) ++t2;
  copy(a, a + n + 1, smx);
  ROF(i, 1, n) chkmax(smx[i], smx[i + 1]);
  ROF(i, 0, t + 1) {
    int mx = a[l[i]];
    while (t1 < n && a[o[t1]] >= mx) {
      mint cur = D.get(n) - D.get(o[t1]) + (a[o[t1]] == smx[o[t1]]);
      C.add(o[t1], cur);
      // D.add(o[t1], cur);
      tv[tc] = cur;
      tx[tc++] = o[t1];
      ++t1;
    }
    ++NUM1;
    FOR(I, 0, tc) D.add(tx[I], tv[I]);
    tc = 0;
    while (t2 < n && (i == 0 || a[o[t2]] >= a[l[i - 1]])) {
      if (l[i] > o[t2]) ans += (C.get(l[i]) - C.get(o[t2])) * f[o[t2]];
      ++t2;
    }
  }
  cout << ans << '\n';
  ++NUM;
  ++NUM1;
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
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

