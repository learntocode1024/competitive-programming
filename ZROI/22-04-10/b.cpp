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
const int N = 505, M = 1e4;
const u32 p = 1e4+7;
int n, k;
int b[N][N];
u32 c[M+5];

inline void red(u32 &x) {
  if (x >= p) x -= p;
}

inline void sol() {
  cin >> n >> k;
  FOR(i,1,n) FOR(j,1,n) cin >> b[i][j];
  /*
  n = 500, k = 100;
  FOR(i,1,n) FOR(j,1,n) b[i][j] = r32(0,M)(rng);
  */
  u32 ans = 0;
  const u32 tot = (p - k * k % p) % p;
  FOR(i,1,n-k+1) {
    FOR(j,0,M) c[j] = 0;
    FOR(u,i,i+k-1) FOR(j,0,k-1) ++c[b[u][j]];
    FOR(r,k,n) {
      FOR(u,i,i+k-1) --c[b[u][r-k]];
      FOR(u,i,i+k-1) ++c[b[u][r]];
      u32 s = 0;
      FOR(i,0,M) {
        if (!c[i]) continue;
        u32 cc = (s << 1) + c[i];
        red(cc += tot);
        ans = (ans + cc * c[i] % p * i) % p;
        s += c[i];
      }
    }
  }
  O(ans*2%p);
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

