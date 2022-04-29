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

#define MULTI
const int N = 5005;
const int mod = 998244353;
int f[N][N];
int n, p, q, a, b;
char s[N];
bool t[N];
int c[N];

inline int q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % mod;
    a >>= 1;
    x = x * x % mod;
  }
  return ret;
}

inline int calc(int n, const int &p, const int &q, const int &a) {
  int m = 0, l = 0;
  FOR(i,1,n) if (t[i]) ++m; else ++l;
  if (l < a) return 0;
  l -= a;
  int fac = 1ll * q_pow(q, m) * q_pow(p, l) % mod;
  if (!l) return fac;
  for (int i = 1, j = n, cnt = -1; i <= m; --j) {
    if (t[j]) {
      c[i] = cnt;
      ++i;
    } else ++cnt;
  }
  if (c[m] < l) return 0;
  f[0][0] = 1;
  FOR(i, 1, m) {
    f[i][0] = f[i-1][0];
    FOR(j,1,c[i]) {
      f[i][j] = f[i][j-1];
      if (j <= c[i-1]) f[i][j] = (f[i][j] + f[i-1][j]) % mod;
    }
  }
  return 1ll * f[m][l] * fac % mod;
}

inline void solve() {
  int x, y;
  rd(n, x, y, a, b);
  cin >> s+1;
  p = 1ll * x * q_pow(y, mod - 2) % mod;
  q = (1 + mod - p) % mod;
  OO(p);
  OO(q);
  int ans = 0;
  if (!b && s[n] == 'L') {
    FOR(i,1,n) t[i] = s[i] == 'R';
    ans = calc(n, p, q, a);
  }
  if (!a && s[1] == 'R') {
    FOR(i,1,n) t[n-i+1] = s[i] == 'L';
    ans = (ans + calc(n, q, p, b)) % mod;
  }
  FOR(i,1,n-1) {
    if (s[i] != 'L' || s[i+1] != 'R') continue;
    FOR(j,1,i) t[j] = s[j] == 'R';
    int cur = calc(i, p, q, a);
    FOR(j,i+1,n) t[n+1-j] = s[j] == 'L';
    cur = 1ll * cur * calc(n-i, q, p, b) % mod;
    ans = (ans + cur) % mod;
  }
  O(ans);
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  f[0][0] = 1;
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

