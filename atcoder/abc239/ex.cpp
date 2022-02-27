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
const int N = 2e5+5, B = 40;
int f[B][N];
const int p = 1e9+7;
unordered_map<int, int> id;
int rk[N];
int n, m;

inline void red(int &x) {
  if (x >= p) x -= p;
}

inline i64 q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

inline i64 inv(int x) {
  return q_pow(x, p - 2);
}

inline void solve() {
  rd(n, m);
  int to = 0;
  for (int i = 1; i <= m; ++i) {
    if (id.find( m / i) != id.end()) {
      to =  (m) / i + 1;
      break;
    }
    id[ (m) / i] = 0;
  }
  FOR(i, 1, to) id[i] = 0;
  int tot = 0;
  for (auto& v : id) {
    v.se = ++tot;
    rk[tot] = v.fi;
  }
  f[0][id[m]] = 1;
  FOR(i, 0, B-1) {
    FOR(j, 2, tot + 1) if (f[i][j]) {
      int S = rk[j];
      int lst = -1;
      FOR(k, 2, min(n, S) + 1) {
        int v =  S / k;
        if (v == lst) break;
        red(f[i+1][id[v]] += f[i][j]);
        lst = v;
      }
      FOR(k,  (m) / n, lst) {
        red(f[i+1][id[k]] += f[i][j]);
      }
    }
  }
  int ans = 0;
  FOR(j, 1, B) {
    int cnt = 0;
    FOR(i, 1, tot + 1) {
      red(cnt += f[j][i]);
    }
    red(ans += 1ll * n * cnt % p * inv(q_pow(n-1, j + 1)) % p);
  }
  println(ans + 2);
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

