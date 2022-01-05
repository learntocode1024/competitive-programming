#include <bits/stdc++.h>
#include "modint"
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

#define MULTI
const int N = 2e5+5;
int n;
typedef MontgomeryModInt<1000000007> mint;
int a[N];
int dis[N];
mint f[N];
int NUM;

struct BIT {
  mint c[N];
  int op[N];
  void add(int x, mint v) {
    for (; x <= n; x += x & -x) {
      if (op[x] != NUM) op[x] = NUM, c[x] = 0;
      c[x] += v;
    }
  }
  mint get(int x) {
    mint ret(0);
    for (; x; x -= x & -x) {
      if (op[x] != NUM) op[x] = NUM, c[x] = 0;
      ret += c[x];
    }
    return ret;
  }
} A, B;

struct PSGT {
  
} T;

inline void get_f() {
  FOR(i, 1, n + 1) {
    mint cnt = A.get(a[i]-1) + 1;
    A.add(a[i], cnt);
    f[i] = cnt + B.get(a[i]-1);
    B.add(a[i], f[i]);
  }
}

inline void solve() {
  cin >> n;
  FOR(i, 1, n + 1) cin >> a[i];
  copy(a + 1, a + n + 1, dis);
  sort(dis, dis + n);
  int ttt = unique(dis, dis + n) - dis;
  FOR(i, 1, n + 1) a[i] = lower_bound(dis, dis + ttt, a[i]) - dis + 1;
  get_f();
  ROF(i, 1, ttt + 1) {
    
  }
  ++NUM;
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

