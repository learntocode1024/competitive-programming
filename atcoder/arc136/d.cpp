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
const int N = 1e6;
i64 f[N];
i64 g[N];
int pw[N];

inline void solve() {
  int n;
  rd(n);
  FOR(i, 0, n) {
    int x;
    rd(x);
    ++f[x];
  }
  FOR(i, 0, N) g[i] = f[i];
  pw[0] = 1;
  FOR(i, 1, 7) pw[i] = pw[i-1] * 10;
  FOR(i, 0, 6) {
    FOR(u, 0, pw[5-i]) FOR(d, 0, pw[i]) {
      int s = u * pw[i+1] + d;
      FOR(k, 1, 10) {
        g[s+k*pw[i]] += g[s+(k-1)*pw[i]];
      }
    }
  }
  i64 ans = 0;
  FOR(i, 0, N) {
    bool ok = 1;
    int v = 0, x = i;
    FOR(j, 0, 6) {
      int t = x % 10;
      if (t >= 5) ok = 0;
      v += (9-t) * pw[j];
      x /= 10;
    }
    if (ok) {
      ans += f[i] * g[v] - f[i];
    } else ans += f[i] * g[v];
  }
  println(ans/2);
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

