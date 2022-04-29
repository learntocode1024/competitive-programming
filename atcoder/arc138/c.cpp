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
const int N = 2e5+5;
int a[N], b[N];
set<pii> s;

inline void sol() {
  int n;
  cin >> n;
  FOR(i,1,n) cin >> a[i], s.insert({a[i], i}), b[i] = -1;
  FOR(_,1,n/2) {
    b[s.begin()->se] = 1;
    s.erase(s.begin());
  }
  i64 ans = 0;
  int k = 1;
  for (auto v : s) ans += v.fi;
  FOR(i,2,n) {
    b[i] += b[i-1];
    if (b[i] < b[k]) k = i;
  }
  wrtln(k%n,ans);
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

