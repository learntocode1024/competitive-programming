#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
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
void O(const A& a) {
  cout << a << '\n';
}
template<typename A, typename... B>
void O(const A& a, const B& ...b) {
  cout << a << ' ';
  O(b...);
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
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template<typename T>
inline void chkmin(T &a, const T b) {
  a = min(a, b);
}
template<typename T>
inline void chkmax(T &a, const T b) {
  a = max(a, b);
}

//#define MULTI
const int N = 3e5+5;
const int p = 998244353;
const i64 rq = 616898040;
map<int, int> f[N];

i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

int a[N];
int c[N][4];
int e[5][5];
int x[N];

inline void solve() {
  int n;
  rd(n);
  FOR(i,1,n) {
    rd(a[i]);
    a[i] = rq * a[i] % p;
  }
  FOR(i,1,n) {
    f[i][i] = p - 1;
    int to = i > 1 ? i-1 : n;
    f[i][to] = a[to];
    to = (i+1)%n+1;
    f[i][to] = (1+p-a[to])%p;
  }
  swap(f[1], f[n+1]);
  FOR(i,2,n-2) {
    i64 w = q_pow(f[i][i+2], p - 2);
    for (auto &x : f[i]) {
      x.se = x.se * w % p;
    }
    FOR(j,1,3) c[i+2][j] = (p - f[i][j]) % p;
    FOR(j,i+1,min(i+3,n+1)) {
      if (f[j].count(i+2)) {
        int w = (p - f[j][i+2]) % p;
        for (auto x : f[i]) {
          f[j][x.fi] = (f[j][x.fi] + 1ll * w * x.se) % p;
        }
        f[j].erase(i+2);
      }
    }
  }
  FOR(i,0,2) FOR(j,1,3) e[i+1][j] = f[n-1+i][j];
  FOR(j,1,4) e[4][j] = 1;
  e[4][4] = p - 1;
  FOR(i,4,n) FOR(j,1,3) e[4][j] = (e[4][j] + c[i][j]) % p;
  FOR(i,1,4) {
    int j = i;
    while (j < 5 && e[j][i] == 0) ++j;
    if (j == 5) continue;
    if (j != i) {
      FOR(k,1,4) swap(e[j][k], e[i][k]);
    }
    for (j = 1; j <= 4; ++j) if (j != i && e[j][i]) {
      int w = q_pow(e[i][i], p-2) * e[j][i] % p;
      w = (p - w) % p;
      FOR(k,1,4) e[j][k] = (e[j][k] + 1ll * w * e[i][k]) % p;
    }
  }
  FOR(i,1,3) {
    x[i] = q_pow(e[i][i], p - 2) * (p - e[i][4]) % p;
  }
  FOR(i,4,n) {
    FOR(j,1,3) x[i] = (x[i] + 1ll * x[j] * c[i][j]) % p;
  }
  FOR(i,1,n) O(x[i]);
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

