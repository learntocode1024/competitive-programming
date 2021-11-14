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

const int N = 2e5+5;
int miu[N], low[N], pr[N], tot;
int n, q;
i64 a[N], b[N], c[N], f[N];
i64 ans[N];

pii x[N];

inline void prework() {
  miu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!low[i]) {
      pr[tot++] = i;
      low[i] = i;
      miu[i] = -1;
    }
    for (int j = 0; j < tot && pr[j] * i <= n; ++j) {
      int to = pr[j] * i;
      low[to] = pr[j];
      if (low[i] == pr[j]) {
        miu[to] = 0;
        break;
      } else miu[to] = -miu[i];
    }
  }
}

i64 f1[N], f2[N], out[N];

inline void solve() {
  cin >> n;
  prework();
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) cin >> b[i];
  cin >> q;
  FOR(i, 0, q) cin >> x[i].fi, x[i].se = i;
  sort(x, x + q);
  b[1] = x[0].fi;
  FOR(i, 1, n + 1) c[i] = b[i] - a[i];
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      f[j] += miu[j / i] * c[i];
    }
  }
  for (int i = 1; i <= n; ++i) ans[0] += abs(f[i]);
  int t1 = 0, t2 = 0;
  i64 ext = 0;
  for (int i = 1; i <= n; ++i) {
    if (miu[i] == -1) f2[++t2] = f[i];
    else if (miu[i] == 1) f1[++t1] = f[i];
    else ext += abs(f[i]);
  }
  sort(f1 + 1, f1 + t1 + 1);
  int p1 = t1;
  while (p1 && f1[p1] >= 0) --p1;
  i64 s1 = 0, s2 = 0, s = 0;
  FOR(i, 1, p1 + 1) s1 -= f1[i];
  FOR(i, p1 + 1, t1 + 1) s2 += f1[i];
  for (int i = 1; i < q; ++i) {
    s += x[i].fi - x[i - 1].fi;
    while (p1 && f1[p1] + s >= 0) {
      s2 += f1[p1];
      s1 += f1[p1];
      --p1;
    }
    ans[i] += s1 + s2 + s * (t1 - p1 - p1) + ext;
  }
  s1 = 0, s2 = 0, s = 0;
  sort(f2 + 1, f2 + t2 + 1);
  reverse(f2 + 1, f2 + t2 + 1);
  int p2 = t2;
  while (p2 && f2[p2] <= 0) --p2;
  FOR(i, 1, p2 + 1) s1 += f2[i];
  FOR(i, p2 + 1, t2 + 1) s2 -= f2[i];
  for (int i = 1; i < q; ++i) {
    s -= x[i].fi - x[i - 1].fi;
    while (p2 && f2[p2] + s <= 0) {
      s2 -= f2[p2];
      s1 -= f2[p2];
      --p2;
    }
    ans[i] += s2 + s1 - s * (t2 - p2 - p2);
  }
  FOR(i, 0, q) {
    out[x[i].se] = ans[i];
  }
  FOR(i, 0, q) cout << out[i] << '\n';
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

