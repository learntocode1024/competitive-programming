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
int n, m;
char a[N], b[N];
int l[N], r[N];

namespace s12 {
int S, s[20];
inline void work() {
  int msk = -1;
  int ans = 0;
  FOR(i, 0, m) {
    s[i] |= 1 << (l[i] - 1);
    if (r[i] < n) s[i] |= 1 << r[i];
  }
  FOR(i, 0, n) {
    S |= int(a[i]) << i;
  }
  FOR(u, 0, 1 << m) {
    int cur = 0;
    FOR(i, 0, m) {
      if ((u >> i) & 1) cur ^= s[i];
    }
    if (cur == S) {
      msk = u;
      ++ans;
    }
  }
  if (msk == -1) {
    cout << "0\nNO\n";
  } else {
    cout << ans << "\nYES\n";
    FOR(i, 0, m) {
      cout << "01"[(msk >> i) & 1];
    }
    cout << '\n';
  }
}
}
const int p = 1e9+7;
namespace s34 {
i64 inv[N], fac[N], ifac[N];
i64 C(int n, int m) {
  if (n < m) return 0;
  if (m < 0 || n < 0) return 0;
  return fac[n] * ifac[m] % p * ifac[n - m] % p;
} 

inline void prework() {
  inv[1] = fac[1] = fac[0] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % p;
    inv[i] = (p - p / i * inv[p % i] % p) % p;
    ifac[i] = ifac[i - 1] * inv[i] % p;
  }
}
i64 dp[N][2];
int c[N];
inline void work() {
  prework();
  dp[0][0] = 1;
  FOR(i, 0, m) ++c[r[i]];
  FOR(i, 1, n) {
    FOR(j, 0, c[i] + 1) {
      if ((j & 1) == a[i]) {
        for (int b = 0; b < 2; ++b) {
          dp[i][b ^ (j & 1)] = (dp[i][b ^ (j + 1)] + dp[i - 1][b] * C(c[i], j)) % p;
        }
      }
    }
  }
  
  FOR(i, 0, c[n] + 1) {

  }
}
}

inline void solve() {
  cin >> n >> m >> a >> b;
  FOR(i, 0, n) a[i] ^= b[i];
  bool B = 1;
  ROF(i, 1, n) a[i] ^= a[i - 1];
  FOR(i, 0, m) {
    cin >> l[i] >> r[i];
    if (l[i] != 1) B = 0;
  }
  if (m <= 20) {
    s12::work();
  } else if (B) s34::work();
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

