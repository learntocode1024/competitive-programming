#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void wrtln(const T &x) { cout << x << '\n'; }
template <typename T, typename... W>
inline void wrtln(const T &x, const W &...b) {
  cout << x << ' ';
  wrtln(b...);
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
const int N = 100;
int t[N];
int a[N];

inline void sol() {
  int n, k;
  cin >> n >> k;
  t[0] = (1 << k) - 1;
  int m = (1 << n) - 1;
  FOR(i,1,n-1) {
    t[i] = (m & (t[i-1]<<1)) | ((t[i-1] >> (n-1)) & 1);
  }
  set<int> s;
  FOR(i,0,n-1) {
    s.insert(t[i]);
    assert(k==__builtin_popcount(t[i]));
  }
  assert(s.size() == n);
  FOR(i,0,n-1) a[i] = t[i];
  if (k%2==0 || (k > 1 && n == k)) {wrtln("No"); return;}
  wrtln("Yes");
  FOR(i,0,m) {
    int u = i ^ (i >> 1);
    int cur = 0;
    FOR(k,0,n-1) if ((u>>k)&1) cur ^= t[k];
    cout << cur << " \n"[i==m];
  }
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

