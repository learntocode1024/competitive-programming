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
const int N = 3e5+5;
struct seg {
  struct node {
    i64 s, tg;
  } a[N<<2];
  inline void down(int p, int l, int r) {
    i64 &tg = a[p].tg;
    int m = (r + l) >> 1;
    a[p<<1].s += tg * (m - l);
    a[p<<1|1].s += tg * (r - m);
    a[p<<1].tg += tg;
    a[p<<1|1].tg += tg;
    tg = 0;
  }
  void add (int p, int l, int r, int s, int t, i64 v) {
    if (l == s && r == t) {
      a[p].s += v * (r - l);
      a[p].tg += v;
      return;
    }
    down(p, l, r);
    int m = (r + l) >> 1;
    if (s < m) add (p<<1, l, m, s, min(m,t), v);
    if (t > m) add (p<<1|1,m,r,max(m,s),t,v);
    a[p].s = a[p<<1].s + a[p<<1|1].s;
  }
  i64 sum(int p, int l, int r, int s, int t) {
    if (l == s && r == t) {
      return a[p].s;
    }
    down(p, l, r);
    int m = (r + l) >> 1;
    i64 ans = 0;
    if (s < m) ans += sum (p<<1, l, m, s, min(m,t));
    if (t > m) ans +=  sum (p<<1|1,m,r,max(m,s),t);
    return ans;
  }
} T;

i64 b[N];

inline void sol() {
  int n, k;
  cin >> n >> k;
  i64 ans = 0;
  FOR(i,1,n) cin >> b[i];
  ROF(i,1,n) b[i] -= b[i-1];
  FOR(I,1,n) T.add(1,1,n+1,I,I+1,b[I]);
  ROF(i,2,n-k+1) {
    int to = i + k;
    i64 h = T.sum(1,1,n+1,1,to);
    i64 c = 0;
    if (h > 0) c = h / k + (h % k != 0);
    T.add(1,1,n+1,i,to,-c);
    ans += c;
  }
  i64 c1 = 0;
  FOR(i,1,k) {
    i64 h = T.sum(1,1,n+1,1,i+1);
    ckmax(c1, h / i + (h % i != 0));
  }
  wrtln(ans+c1);
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

