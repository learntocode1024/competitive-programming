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
#define MULTI
const int N = 5e5+5;
i64 s[N];
int a[N];
int f[N];
int mx[N];
map<i64, int> id;
struct sgT {
  int mx[N<<2];
  int get(int p, int l, int r, int s, int t) {
    if (l == s && r == t) return mx[p];
    int ret = -1e8;
    int m = (l + r) >> 1;
    if (s < m) ckmax(ret,get(p<<1,l,m,s,min(m,t)));
    if (t > m) ckmax(ret,get(p<<1|1,m,r,max(m,s),t));
    return ret;
  }
  void set(int p, int l, int r, int s, int v) {
    ckmax(mx[p], v);
    if (r - l == 1) return;
    int m = (l + r) >> 1;
    if (s < m) set(p<<1,l,m,s,v);
    else set(p<<1|1,m,r,s,v);
  }
} L, H;

inline void sol() {
  int n;
  cin >> n;
  FOR(i,1,n) cin >> a[i], s[i] = s[i-1] + a[i];
  f[0] = 0;
  id.clear();
  id[0] = 0;
  FOR(i,1,n) id[s[i]] = 0;
  int tot = 0;
  for (auto &x : id) {
    x.se = ++tot;
  }
  FOR(i,0,n+4) mx[i] = -1e8;
  FOR(i,1,(n+4)<<2) L.mx[i] = H.mx[i] = -1e8;
  mx[id[0]] = 0;
  L.set(1,1,n+3,id[0],0);
  H.set(1,1,n+3,id[0],0);
  FOR(i,1,n) {
    int cid = id[s[i]];
    f[i] = -1e8;
    ckmax(f[i], mx[cid]);
    if (cid > 1) ckmax(f[i], L.get(1,1,n+3,1,cid) + i);
    ckmax(f[i], H.get(1,1,n+3,cid+1,n+3) - i);
    ckmax(mx[cid], f[i]);
    L.set(1,1,n+3,cid,f[i]-i);
    H.set(1,1,n+3,cid,f[i]+i);
  }
  O(f[n]);
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

