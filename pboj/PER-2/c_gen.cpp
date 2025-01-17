#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(const T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(const T &x, const W &...b) {
  cin >> x;
  rd(b...);
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
const int N = 16;
const int P = 1e9+7;
int a[N];
unordered_map<int, int> S;

inline bool calc() {
  S.clear();
  FOR(u,0,1<<(N-1)) {
    int x = a[0];
    FOR(i,0,N-2) {
      if ((u>>i)&1) x = 1ll * x * a[i+1] % P;
      else x = (x + a[i+1]) % P;
    }
    S[x] = u;
  }
  err("%ld\n", S.size());
  return S.size() == (1<<(N-1));
}

inline void sol() {
  do {
    FOR(i,1,N-1) a[i] = r32(1,P-1)(rng);
  } while (!calc());
  cout << "const int a[16] = {";
  FOR(i,0,N-1) cout << a[i] << ",}"[i==N-1];
  cout << ";\n";
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

