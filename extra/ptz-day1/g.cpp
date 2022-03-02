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
const int N = 1e5+5;
int n;
struct mat {
  i64 a[4];
  mat() = default;
  mat(int _a, int _b, int _c, int _d) {
    a[0] = _a, a[1] = _b, a[2] = _c, a[3] = _d;
  }
  mat operator* (const mat &b) {
    mat c;
    c.a[0] = min(a[0] + b.a[0], a[1] + b.a[2]);
    c.a[1] = min(a[0] + b.a[1], a[1] + b.a[3]);
    c.a[2] = min(a[2] + b.a[0], a[3] + b.a[2]);
    c.a[3] = min(a[2] + b.a[1], a[3] + b.a[3]);
    return c;
  }
  i64 operator() (int x, int y) {
    return min(min(x+a[0], y+a[1]), min(x+a[2], y+a[3]));
  }
} c[N<<3];

int P[N], A[N], B[N], a[N<<1], b[N<<1];
bool vis[N];
int m;

void build(int p, int l, int r) {
  if (r - l == 1) {
    c[p] = mat(a[l],a[l], b[l]+b[l-1], b[l]);
    return;
  }
  int mid = (l + r) >> 1;
  build(p<<1, l, mid);
  build(p<<1|1, mid, r);
  c[p] = c[p<<1]*c[p<<1|1];
}

mat prod(int p, int l, int r, int s, int t) {
  if (l == s && r == t) {
    return c[p];
  }
  int mid = (l + r) >> 1;
  if (t <= mid) return prod(p<<1, l, mid, s, t);
  if (s >= mid) return prod(p<<1|1, mid, r, s, t);
  return prod(p<<1, l, mid, s, mid) * prod(p<<1|1, mid, r, mid, t);
}

i64 run() {
  if (m == 1) return 0;
  if (m == 2) return min(a[1] + a[2], b[1] + b[2]);
  FOR(i, 1, m + 1) a[i+m] = a[i], b[i+m] = b[i];
  build(1, 1, m*2+1);
  i64 ret = 0;
  FOR(i, 1, m + 1) ret += b[i];
  FOR(i, 1, m + 1) chkmin(ret, prod(1, 1, m*2+1, i+1, i + m)(a[i], 1e9));
  return ret;
}

inline void solve() {
  rd(n);
  FOR(i, 1, n + 1) rd(P[i]);
  FOR(i, 1, n + 1) rd(A[i]);
  FOR(i, 1, n + 1) rd(B[i]);
  i64 ans = 0;
  FOR(i, 1, n + 1) if (!vis[i]) {
    m = 0;
    int u = i;
    while (!vis[u]) {
      ++m;
      a[m] = A[u];
      b[m] = B[u];
      vis[u] = 1;
      u = P[u];
    }
    ans += run();
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

