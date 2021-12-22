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

//#define MULTI
const int N = 2e6+5;
int op[N], t[N], x[N], y[N];
int n;
int tmp[N], tot;
  int a[N], b[N];
  int ra[N], rb[N];
  inline void add(int *c, int x, int v) {
    for (; x <= tot; x += x & -x) c[x] += v;
  }

inline void work() {
  int k = 0;
    int sa = 0, sb = 0;
  ROF(i, 0, 21) {
    int t = 1 << i;
    if (k + t <= tot && sa + a[k + t] < sb + b[k + t]) sa += a[k + t], sb += b[k + t], k += t;
  }
  while (k < tot && sa <= min(sa + ra[k + 1], sb - rb[k])) sa = min(sa + ra[k + 1], sb - rb[k]), ++k;
  if (!sa) println("Peace");
  else println(tmp[k - 1], sa<<1);
}

inline void solve() {
  cin >> n;
  FOR(i, 0, n) {
    rd(op[i]);
    if (op[i] == 1) {
      rd(t[i], x[i], y[i]);
      tmp[tot++] = x[i];
    } else cin >> t[i], --t[i];
  }
  sort(tmp, tmp + tot);
  tot = unique(tmp, tmp + tot) - tmp;
  FOR(i, 0, n) x[i] = lower_bound(tmp, tmp + tot, x[i]) - tmp + 1;
  FOR(i, 0, n) {
    if (op[i] == 1) {
      if (t[i] == 0) add(a, x[i], y[i]), ra[x[i]] += y[i];
      else add(b, 1, y[i]), add(b, x[i] + 1, -y[i]), rb[x[i]] += y[i];
    } else {
      if (t[t[i]] == 0) add(a, x[t[i]], -y[t[i]]), ra[x[t[i]]] -= y[t[i]];
      else add(b, 1, -y[t[i]]), add(b, x[t[i]] + 1, -y[t[i]]), rb[x[t[i]]] -= y[t[i]];
    }
    work();
  }
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  // ios::sync_with_stdio(0);
  // cin.tie(0);
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

