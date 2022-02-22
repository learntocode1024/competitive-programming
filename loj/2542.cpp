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
const int N = 20;
const int p = 998244353;
int q_pow(i64 a, int x) {
  i64 ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

int inv(int x) {
  return q_pow(x, p - 2);
}

vector<int> g[N];
int k[N], b[N];
int msk;
int f[1<<N];

void calc(int u, int fa) {
  k[u] = b[u] = 0;
  if ((msk >> (u - 1)) & 1) return;
  for (auto v : g[u]) if (v != fa) {
    calc(v, u);
    k[u] = (k[u] + k[v]) % p;
    b[u] = (b[u] + b[v]) % p;
  }
  int d = g[u].size();
  k[u] = inv(d + p - k[u]);
  b[u] = 1ll * (d + b[u]) * k[u] % p;
}

inline void solve() {
  int n, q, x;
  rd(n, q, x);
  FOR(i, 1, n) {
    int u, v;
    rd(u, v);
    g[u].pb(v);
    g[v].pb(u);
  }
  FOR(u, 1, 1 << n) {
    if ((u >> (x - 1)) & 1) continue;
    msk = u;
    calc(x, 0);
    if (__builtin_parity(u)) f[u] = b[x];
    else f[u] = (p - b[x]) % p;
  }
  for (int i = 1; i < (1 << n); i <<= 1) {
    for (int j = 0; j < (1 << n); j += i << 1) {
      for (int k = j; k < j + i; ++k) {
        f[k+i] = (f[k+i] + f[k]) % p;
      }
    }
  }
  while (q--) {
    int s;
    rd(s);
    int u = 0;
    while (s--) {
      int t;
      rd(t);
      u |= 1 << (t-1);
    }
    println(f[u]);
  }
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

