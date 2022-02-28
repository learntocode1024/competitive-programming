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
const int N = 1e5+5;
int c[N];
int n;
inline void add(int x) {
  for (; x <= n; x += x & -x) ++c[x];
}
inline int get(int x) {
  int ret = 0;
  for (; x; x -= x & -x) ret += c[x];
  return ret;
}

inline int sum(int l, int r) {
  if (l > r) return 0;
  return get(r) - get(l-1);
}

int h[N], rk[N];
i64 d2[N], d1[N], f[N];

inline void solve() {
  int L, R;
  rd(n, L, R);
  FOR(i, 1, n + 1) {
    rd(h[i]);
    rk[h[i]] = i;
  }
  i64 ans = 0;
  int m = 1;
  ROF(i, 1, n+1) {
    ++m;
    int x = rk[i];
    add(x);
    int c = get(x);
    c = min(c, m - c);
    ++d2[1];
    --d2[m/2+1];
    --d2[(m+1)/2+1];
    ++d2[m+1];
    if (c < m/2) {
      ++d2[m/2+1];
      ++d2[(m+1)/2+1];
      --d2[c+1];
      --d2[m-c+1];
    }
  }
  FOR(i, 1, n + 1) d1[i] = d1[i-1] + d2[i];
  FOR(i, 1, n + 1) f[i] = f[i-1] + d1[i];
  FOR(i, L, R + 1) ans ^= f[i];
  println(ans);
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

