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
const int N = 3e5+5;
int n, q;
i64 MOD, a[N], b[N], c[N], f[N];
int cnt;

inline void solve() {
  cin >> n >> q >> MOD;
  FOR(i, 1, n + 1) cin >> a[i];
  FOR(i, 1, n + 1) cin >> b[i];
  FOR(i, 1, n + 1) a[i] = (a[i] + MOD - b[i]) % MOD;
  FOR(i, 2, n + 1) c[i] = (a[i] - a[i-1] - a[i-2] + 2*MOD) % MOD;
  c[1] = a[1];
  f[1] = 1, f[2] = 1;
  FOR(i, 3, n + 1) f[i] = (f[i-1] + f[i-2])%MOD;
  FOR(i, 1, n + 1) if (c[i] != 0) ++cnt;
  FOR(i, 0, q) {
    char ch;
    int l, r;
    cin >> ch >> l >> r;
    if (ch == 'A') {
      if (c[l] != 0) --cnt;
      c[l] = (c[l] + 1) % MOD;
      if (c[l] != 0) ++cnt;
      if (r+1<=n) {
        if (c[r+1] != 0) --cnt;
        c[r+1] = (c[r+1] + MOD - f[r-l+2]) % MOD;
        if (c[r+1] != 0) ++cnt;
      }
      if (r+2<=n) {
        if (c[r+2] != 0) --cnt;
        c[r+2] = (c[r+2] + MOD - f[r-l+1]) % MOD;
        if (c[r+2] != 0) ++cnt;
      }
    } else {
      if (c[l] != 0) --cnt;
      c[l] = (c[l] + MOD - 1) % MOD;
      if (c[l] != 0) ++cnt;
      if (r+1<=n) {
        if (c[r+1] != 0) --cnt;
        c[r+1] = (c[r+1] + f[r-l+2]) % MOD;
        if (c[r+1] != 0) ++cnt;
      }
      if (r+2<=n) {
        if (c[r+2] != 0) --cnt;
        c[r+2] = (c[r+2] + f[r-l+1]) % MOD;
        if (c[r+2] != 0) ++cnt;
      }
    }
    println((cnt==0) ? "YES" : "NO");
  }
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

