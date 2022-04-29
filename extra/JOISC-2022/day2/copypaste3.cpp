#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 2505;
const int p = 2147483587, q = 1129;
i64 H[N], pw[N];
char s[N];
int n, a, b, c;
i64 f[N][N];
inline i64 h(int l, int r) {
  return (H[r] - H[l-1] * pw[r - l + 1]);
}

inline void solve() {
  rd(n);
  cin >> s + 1;
  rd(a,b,c);
  FOR(l,1,n) FOR(r,1,n) f[l][r] = 1e18;
  FOR(i,1,n) f[i][i] = a;
  pw[0] = 1;
  FOR(i,1,n) pw[i] = 1ll * pw[i-1] * q;
  FOR(i,1,n) H[i] = (1ll * H[i-1] * q + s[i]);
  for (int len = 1; len <= n; ++len) for (int l = 1; l < n; ++l) {
    int r = l + len - 1;
    if (r > n) continue;
    chkmin(f[l][r], f[l][r-1] + a);
    chkmin(f[l][r], f[l+1][r] + a);
    const i64 cur = h(l,r);
    i64 to = f[l][r] + b + c;
    for (int i = r + 1; i + len - 1 <= n; ++i) {
      if (h(i,i+len-1) == cur) {
        i += len - 1;
        to += c;
      } else {
        to += a;
      }
      chkmin(f[l][i], to);
    }
  }
  O(f[1][n]);
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

