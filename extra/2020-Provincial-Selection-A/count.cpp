#include <bits/stdc++.h>
using namespace std;
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
void print(const A& a) {
  cout << a;
}
template<typename A, typename... B>
void print(const A& a, const B& ...b) {
  cout << a;
  print(b...);
}
template<typename A>
void println(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void println(const A& a, const B& ...b) {
  cout << a << ' ';
  println(b...);
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
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 35, M = N*N;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}
inline i64 inv(int x) { return q_pow(x, p-2); }
struct poly1 {
  int x[2];
  int &operator[] (int i) { return x[i]; }
  const int &operator[] (int i) const { return x[i]; }
  poly1 operator+ (const poly1 &rhs) {
    poly1 ret = *this;
    red(ret[0] += rhs[0]);
    red(ret[1] += rhs[1]);
    return ret;
  }
  poly1 operator- () const {
    poly1 ret;
    red(ret[0] = p - x[0]);
    red(ret[1] = p - x[1]);
    return ret;
  }
  poly1 operator- (const poly1 &rhs) {
    poly1 ret = *this;
    red(ret[0] += p - rhs[0]);
    red(ret[1] += p - rhs[1]);
    return ret;
  }
  poly1 operator* (const poly1 &rhs) {
    poly1 ret;
    ret[0] = 1ll * x[0] * rhs[0] % p;
    ret[1] = (1ll * x[1] * rhs[0] + 1ll * x[0] * rhs[1]) % p;
    return ret;
  }
  inline poly1 inv() const {
    poly1 ret;
    ret[0] = ::inv(x[0]);
    ret[1] = 1ll * ret[0] * ret[0] % p * (p - x[1]) % p;
    return ret;
  }
  poly1 operator/ (const poly1 &rhs) {
    return *this * rhs.inv();
  }
  bool operator!=(const poly1 &rhs) const {
    return (x[0] != rhs[0] || x[1] != rhs[1]);
  }
  bool operator==(const poly1 &rhs) const {
    return (x[0] == rhs[0] && x[1] == rhs[1]);
  }
};
const poly1 id = {1, 0}, zero = {0, 0};
int phi[152502], low[152502], pri[152502], tot;
int u[M], v[M], w[M];
poly1 a[N][N];
int n, m;

int kirchhoff() {
  bool sgn = 0;
  FOR(i, 0, n - 1) {
    int j = i;
    while (j < n - 1 && a[j][i] == zero) ++j;
    if (j == n - 1) continue;
    if (j != i) {
      sgn ^= 1;
      FOR(k, 0, n - 1) swap(a[i][k], a[j][k]);
    }
    for (j = 0; j < n - 1; ++j) if (j != i && a[j][i] != zero) {
      poly1 c = -(a[j][i]/a[i][i]);
      FOR(k, 0, n - 1) a[j][k] = a[j][k] + a[i][k] * c;
    }
  }
  poly1 ans = id;
  FOR(i, 0, n - 1) ans = ans * a[i][i];
  if (sgn) return (p - ans[1]) % p;
  return ans[1];
}

inline void solve() {
  phi[1] = 1;
  FOR(i, 2, 152502) {
    if (!low[i]) {
      low[i] = pri[tot++] = i;
      phi[i] = i - 1;
    }
    for (int j = 0; j < tot && pri[j] * i < 152502; ++j) {
      int to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        phi[to] = phi[i] * pri[j];
        break;
      } else {
        phi[to] = phi[i] * (pri[j] - 1);
      }
    }
  }
  cin >> n >> m;
  FOR(i, 0, m) cin >> u[i] >> v[i] >> w[i], --u[i], --v[i];
  int ans = 0;
  FOR(d, 1, 152502) {
    int cnt = 0;
    FOR(i, 0, m) if (w[i] % d == 0) ++cnt;
    if (cnt < n - 1) continue;
    FOR(i, 0, n) FOR(j, 0, n) a[i][j] = zero;
    FOR(i, 0, m) if (w[i] % d == 0) {
      a[u[i]][u[i]] = a[u[i]][u[i]] + poly1{1, w[i]};
      a[v[i]][v[i]] = a[v[i]][v[i]] + poly1{1, w[i]};
      a[v[i]][u[i]] = a[v[i]][u[i]] - poly1{1, w[i]};
      a[u[i]][v[i]] = a[u[i]][v[i]] - poly1{1, w[i]};
    }
    ans = (ans + 1ll * phi[d] * kirchhoff()) % p;
  }
  println(ans);
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

