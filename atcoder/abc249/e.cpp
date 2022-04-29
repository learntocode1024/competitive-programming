#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
#ifndef MISAKA
#define err(...)
#else
#define err(...) fprintf(stderr, __VA_ARGS__)
#endif
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef long double dbl;
typedef pair<int, int> pii;
typedef uniform_int_distribution<int> r32;
typedef uniform_int_distribution<i64> r64;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define shuf(L, R) shuffle((L), (R), rng)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T> inline void ckmin(T &a, const T &b) { a = min(a, b); }
template <typename T> inline void ckmax(T &a, const T &b) { a = max(a, b); }
//#define IOFILE "filename"
//#define MULTI
const int N = 3010;
int f[N][N];

inline void sol() {
  int n, p;
  cin >> n >> p;
  f[0][0] = 1;
  f[0][1] = p - 1;
  int ans = 0;
  FOR(i,0,n-1) {
    FOR(j,1,n) f[i][j] = (f[i][j-1] + f[i][j]) % p;
    ans = (ans + f[i][n]) % p;
    FOR(j,0,n) {
      int cur = 25ll * f[i][j] % p;
      if (i == 0) cur = (cur + f[i][j]) % p;
      if (j + 1 <= n) {
        f[i+2][j+1] = (f[i+2][j+1] + cur) % p;
        int r = min(j+10, n+1);
        f[i+2][r] = (f[i+2][r] + p - cur) % p;
      }
      if (j + 10 <= n) {
        f[i+3][j+10] = (f[i+3][j+10] + cur) % p;
        int r = min(j+100, n+1);
        f[i+3][r] = (f[i+3][r] + p - cur) % p;
      }
      if (j + 100 <= n) {
        f[i+4][j+100] = (f[i+4][j+100] + cur) % p;
        int r = min(j+1000, n+1);
        f[i+4][r] = (f[i+4][r] + p - cur) % p;
      }
      if (j + 1000 <= n) {
        f[i+5][j+1000] = (f[i+5][j+1000] + cur) % p;
        int r = min(j+10000, n+1);
        f[i+5][r] = (f[i+5][r] + p - cur) % p;
      }
    }
  }
  O(ans);
}

int main() {
#ifndef MISAKA
#ifdef IOFILE
  freopen(IOFILE ".in", "r", stdin);
  freopen(IOFILE ".out", "w", stdout);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
#endif
#ifdef MULTI
  int T;
  cin >> T;
  while (T--)
#endif
    sol();
  return 0;
}

