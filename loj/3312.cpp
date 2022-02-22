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
const int N = 0;
const int p = 998244353;
int n, k;
i64 ans, iv;
i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

i64 inv(i64 x) {
  x %= p;
  return q_pow(x, p-2);
}

i64 cnt(i64 x) {
  return x * (x + 1) / 2;
}

i64 tr[3][3], f[3][3], g[3][3];

inline void mul(i64 a[3][3], i64 b[3][3], i64 c[3][3]) {
  memset(g, 0, sizeof(g));
  FOR(i, 0, 3) FOR(j, 0, 3) FOR(k, 0, 3) {
    g[i][j] = (g[i][j] + b[i][k] * c[k][j]) % p;
  }
  memcpy(a, g, sizeof(g));
}

inline int getans() {
  int kk = k;
  memset(f, 0, sizeof(f));
  f[0][0] = f[1][1] = f[2][2] = 1;
  while (kk) {
    if (kk & 1) mul(f, f, tr);
    mul(tr, tr, tr);
    kk >>= 1;
  }
  return f[0][1];
}

void build(i64 l, i64 r, i64 l1, i64 r1) {
  i64 p1, p2, p3, p4, p5;
  p1 = p2 = p3 = p4 = p5 = 0;
  if (!l1) {
    p1 = iv;
    p2 = (1 + p - iv) % p;
  } else {
    if (l == l1) {
      p1 = l * (r1 - r) % p * iv % p;
      p3 = (cnt(n - r) - cnt(n - r1)) % p * iv % p;
    } else {
      p1 = (l - l1) * (n - r + 1) % p * iv % p;
      p3 = (cnt(l - 1) - cnt(l1 - 1)) % p * iv % p;
    }
    p2 = (cnt(n - l) - cnt(n - r) + l * (r - l)) % p * iv % p;
    p5 = l1 * (n - r1 + 1) % p * iv % p;
    p4 = p1 + p2 + p3 + p5;
    p4 = (1 + p - p4 % p) % p;
  }
  memset(tr, 0, sizeof(tr));
  tr[0][0] = 1;
  tr[0][1] = p1;
  tr[2][1] = p3;
  tr[1][1] = (p4+p5) % p;
  tr[0][2] = (p1+p5) % p;
  tr[2][2] = (p3+p4) % p;
  ans = (ans + getans()) % p;
  if (l == r) return;
  int m;
  cin >> m;
  build(l, m, l, r);
  build(m+1, r, l, r);
}

inline void solve() {
  rd(n, k);
  iv = inv((1ll * n * (n + 1)) / 2);
  build(1, n, 0, 0);
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

