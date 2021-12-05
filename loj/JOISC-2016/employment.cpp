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
int a[N];
int T[N], B[N], C[N], D[N];
int d[N<<1], c[N<<1], tot = 1;
int n, m;
inline void ch(int x, int v) {
for (; x <= tot; x += x & -x) {
  c[x] += v;
}
}

inline int get(int x) {
int ret = 0;
for (; x; x -= x & -x) {
  ret += c[x];
}
return ret;
}
inline void solve() {
  rd(n, m);
  FOR(i, 1, n + 1) rd(a[i]), d[tot++] = a[i];
  FOR(i, 0, m) {
    rd(T[i]);
    if (T[i] == 1) rd(B[i]), d[tot++] = B[i];
    else rd(C[i], D[i]), d[tot++] = D[i];
  }
  sort(d, d + tot);
  tot = unique(d, d + tot) - d;
  FOR(i, 0, n + 1) a[i] = lower_bound(d, d + tot, a[i]) - d + 1;
  FOR(i, 0, m) D[i] = lower_bound(d, d + tot, D[i]) - d + 1;
  FOR(i, 0, m) B[i] = lower_bound(d, d + tot, B[i]) - d + 1;
  FOR(i, 0, n) if (a[i] < a[i + 1]) ch(a[i] + 1, 1), ch(a[i + 1] + 1, -1);
  FOR(i, 0, m) {
    if (T[i] == 1) {
      cout << get(B[i]) << '\n';
    } else {
      int x = C[i];
      if (a[x - 1] < a[x]) ch(a[x - 1] + 1, -1), ch(a[x] + 1, 1);
      if (a[x] < a[x + 1]) ch(a[x] + 1, -1), ch(a[x + 1] + 1, 1);
      a[x] = D[i];
      if (a[x - 1] < a[x]) ch(a[x - 1] + 1, 1), ch(a[x] + 1, -1);
      if (a[x] < a[x + 1]) ch(a[x] + 1, 1), ch(a[x + 1] + 1, -1);
    }
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

