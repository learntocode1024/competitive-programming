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
const int p = 100003;
int low[N], pri[N], tot;
bool ok[N], a[N];
vector<int> f[N];
int fac[N], d[N], inv[N];

inline void solve() {
  low[1] = ok[1] = 1;
  FOR(i,2,N) {
    if (!low[i]) {
      low[i] = pri[tot++] = i;
      ok[i] = 1;
    }
    for (int j = 0; j < tot && pri[j] <= low[i] && pri[j] * i < N; ++j) {
      int to = i * pri[j];
      low[to] = pri[j];
      ok[to] = (pri[j] != low[i]) && ok[i];
    }
  }
  FOR(i, 1, N) {
    for (int j = 1; j * i < N; ++j) if (ok[j]) {
      f[j*i].pb(i);
    }
  }
  fac[1] = fac[0] = inv[1] = 1;
  FOR(i, 2, N) {
    fac[i] = 1ll * fac[i - 1] * i % p;
    inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
  }
  int n, k;
  rd(n, k);
  d[n] = 1;
  ROF(i, k + 1, n) {
    d[i] = (1ll * d[i+1] * (n - i) % p * inv[i] % p + 1ll * n * inv[i] % p) % p;
  }
  FOR(i, 1, n + 1) {
    int t;
    cin >> t;
    if (t == 1) for (auto v : f[i]) {
      a[v] ^= 1;
    }
  }
  int cnt = 0;
  FOR(i, 1, n + 1) {
    cnt += a[i];
  }
  if (cnt <= k) println(1ll * cnt * fac[n] % p);
  else {
    int ans = k;
    FOR(i, k + 1, cnt + 1) ans += d[i];
    println(1ll * ans * fac[n] % p);
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

