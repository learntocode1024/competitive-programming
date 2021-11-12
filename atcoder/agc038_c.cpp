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

const int N = 1e6+5;
const int p = 998244353;
inline void red(int &x) { if (x >= p) x -= p; }
int low[N], pri[N], inv[N], tpri;
int f[N];
int a[N];
vector<int> g[N];

i64 q_pow(i64 x, int y) {
  i64 ret = 1;
  while (y) {
    if (y & 1) ret = ret * x % p;
    x = x * x % p;
    y >>= 1;
  }
  return ret;
}

inline void solve() {
  low[1] = f[1] = 1;
  inv[1] = 1;
  for (int i = 2; i <= 1000000; ++i) {
    if (!low[i]) {
      pri[tpri++] = i;
      low[i] = i;
      inv[i] = q_pow(i, p - 2);
      red(f[i] = inv[i] + p - 1);
    }
    for (int j = 0; j < tpri && pri[j] * i <= 1000000; ++j) {
      int to = pri[j] * i;
      low[to] = pri[j];
      if (pri[j] == low[i]) {
        f[to] = 1ll * f[i] * inv[pri[j]] % p;
        break;
      } else {
        f[to] = 1ll * f[i] * f[pri[j]] % p;
      }
    }
  }
  FOR(i, 1, 1000001) {
    for (int j = i; j <= 1000000; j += i) {
      g[j].pb(i);
    }
  }
  int n;
  cin >> n;
  int ret = 0;
  FOR(_, 0, n) {
    int x;
    cin >> x;
    int ans = 0;
    for (auto v : g[x]) {
      red(ans += 1ll * a[v] * f[v] % p);
      red(a[v] += x);
    }
    red(ret += 1ll * ans * x % p);
  }
  println(ret);
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

