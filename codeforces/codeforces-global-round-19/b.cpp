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

#define MULTI
const int N = 105;
int a[N], c[N][N];
bool v[N];
int f[N];
int n;

int mex(int l, int r) {
  FOR(i, l, r + 1) if (a[i] <= n) {
    v[a[i]] = 1;
  }
  int ret = 0;
  FOR(i, 0, n + 2) {
    if (!v[i]) {
      ret = i;
      break;
    }
  }
  FOR(i, l, r + 1) if (a[i] <= n) {
    v[a[i]] = 0;
  }
  return ret;
}

inline void solve() {
  rd(n);
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) FOR(j, i, n + 1) {
    c[i][j] = mex(i, j);
  }
  int ans = 0;
  FOR(l, 1, n + 1) FOR(r, l, n + 1) {
    f[l-1] = 0;
    FOR(i, l, r + 1) {
      f[i] = -1e8;
      FOR(j, l-1, i) chkmax(f[i], f[j] + c[j+1][i] + 1);
    }
    // if (r > l) chkmax(f[r], 2);
    ans += f[r];
  }
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

