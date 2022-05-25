/** @file
 * @ingroup min_plus_matrix
put the distance from both exits on layer $i-1$ to them on layer $i$ into a matrix $A_i$.
We can get all the information needed to answer a query by multiplying these matrix in range.
 */
#include <bits/stdc++.h>
using namespace std;
template <typename T> inline void O(const T &x) { cout << x << '\n'; }
template <typename T, typename... W> inline void O(const T &x, const W &...b) {
  cout << x << ' ';
  O(b...);
}
template <typename T> inline void rd(T &x) { cin >> x; }
template <typename T, typename... W> inline void rd(T &x, W &...b) {
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
const int N = 1e5+5;
i64 f[N][2][2], g[N<<2][2][2];

#define F2(x) FOR(x,0,1)
typedef i64 mat[2][2];

i64 t[2][2];
i64 h[2][2];
void mul(mat c, mat b, mat a) {
  F2(i) F2(j) t[i][j] = 1e12;
  F2(i) F2(j) F2(k) ckmin(t[i][j], a[i][k] + b[k][j]);
  F2(i) F2(j) c[i][j] = t[i][j];
}

void build(int p, int l, int r) {
  if (r == l) {
    F2(i) F2(j) g[p][i][j] = f[l][i][j];
    return;
  }
  int m = (l + r) >> 1;
  build(p<<1, l, m);
  build(p<<1|1, m+1, r);
  mul(g[p], g[p<<1], g[p<<1|1]);
}

int n;
int a[N], b[N];

int d(int x, int y) {
  int z = max(x, y);
  if (z == x) return y;
  return 2 * z - x;
}

void get(int p, int l, int r, int s, int t) {
  if (s <= l && t >= r) {
    mul(h, h, g[p]);
    return;
  }
  if (r < s || l > t) return;
  int m = (l + r) >> 1;
  get(p<<1, l, m, s, t);
  get(p<<1|1, m+1, r, s, t);
}

inline void sol() {
  rd(n);
  FOR(i,1,n-1) {
    int d1, d2;
    rd(d1, a[i], b[i], d2);
  }
  a[n] = a[n-1];
  b[n] = b[n-1];
  FOR(i,2,n) {
    f[i][0][0] = 1+abs(a[i]-a[i-1]);
    f[i][1][0] = 1+2*i-a[i-1]-b[i];
    f[i][0][1] = 1+2*i-a[i]-b[i-1];
    f[i][1][1] = 1+abs(b[i]-b[i-1]);
  }
  build(1,2,n);
  int q;
  rd(q);
  while (q--) {
    h[1][0] = h[0][1] = 1e12;
    h[0][0] = h[1][1] = 0;
    i64 dis = -1;
    int x, y, z, w;
    rd(x, y, z, w);
    int s = max(x, y), t = max(z, w);
    if (s > t) {
    swap(x, z);
    swap(y, w);
    swap(s, t);
    }
    if (s == t) {
      dis = abs(d(x, y) - d(z, w));
    } else {
    if (t - s > 1) get(1, 2, n, s+1, t-1);
    int d1 = abs(d(x, y) - d(s, a[s])), d2 = abs(d(x, y) - d(b[s], s));;
    i64 r1 = min(d1 + h[0][0], d2 + h[0][1]);
    i64 r2 = min(d1 + h[1][0], d2 + h[1][1]);
    dis = min(r1 + abs(d(z, w) - d(t, a[t-1])), r2 + abs(d(z, w) - d(b[t-1], t))) + 1;
    }
    O(dis);
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

