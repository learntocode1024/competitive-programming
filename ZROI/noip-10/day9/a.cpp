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

const int N = 20;
const int p = 1e9+7;
inline void red(int &x) { if (x >= p) x -= p; }
int m;

struct mat {
  int a[N][N];
  int* operator[] (u32 x) { return a[x]; }
  const int* operator[] (u32 x) const { return a[x]; }
  mat operator* (const mat &r) {
    mat ret;
    memset(&ret, 0, sizeof(ret));
    FOR(i, 0, m) FOR(j, 0, m) FOR(k, 0, m) red(ret[i][j] += 1ll * a[i][k] * r[k][j] % p);
    return ret;
  }
};
i64 c[N];

mat id;

mat q_pow(mat a, i64 k) {
  mat ret = id;
  while (k) {
    if (k & 1) ret = ret * a;
    a = a * a;
    k >>= 1;
  }
  return ret;
}

inline void solve() {
  int n;
  cin >> n >> m;
  memset(&id, 0, sizeof(id));
  FOR(i, 0, m) id[i][i] = 1;
  while (n--) {
    int x, y;
    cin >> x >> y;
    c[y % m] += x;
  }
  mat all = id;
  FOR(i, 0, m) {
    mat cur = id;
    FOR(j, 0, m) ++cur[j][(i + j) % m];
    all = all * q_pow(cur, c[i]);
  }
  int ans;
  red(ans = all[0][0] + p - 1);
  cout << ans << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
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
