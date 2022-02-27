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
const int N = 40000;
const int p = 998244353;
inline int q_pow(i64 x, int a) {
  i64 ret = 1;
  while (a) {
    if (a & 1) ret = ret * x % p;
    x = x * x % p;
    a >>= 1;
  }
  return ret;
}

int a[N][N];
map<pii, int> id, w;
int n, m;

inline int inv(int x) {
  return q_pow(x,p-2);
}
const int i4 = 748683265;
const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};

inline void solve() {
  rd(n);
  m = n;
  FOR(i, 0, n) {
    int x, y, c;
    rd(x, y, c);
    id[{x,y}] = i;
    w[{x,y}] = c;
    FOR(k, 0, 4) {
      int s = x + dx[k], t = y + dy[k];
      if (id.find({s,t}) == id.end()) {
        id[{s,t}] = m++;
      }
    }
  }
  for (auto u : id) {
    pii x = u.fi;
    a[u.se][u.se] = 1;
    a[u.se][m] = w[x];
    FOR(k, 0, 4) {
      int s = x.fi + dx[k], t = x.se + dy[k];
      if (id.find({s,t}) == id.end() || id[{s,t}] >= n) continue;
      a[u.se][id[{s,t}]] = p - i4;
    }
  }
  FOR(i, 0, m) {
    FOR(j, i, m) {
      if (a[j][i] != 0) {
        if (j == i) break;
        FOR(k, 0, m+1) swap(a[j][k], a[i][k]);
        break;
      }
    }
    int iv = inv(a[i][i]);
    FOR(k, i, m + 1) a[i][k] = 1ll * a[i][k] * iv % p;
    FOR(j, 0, m) if (j != i && a[j][i] != 0) {
      int c = a[j][i];
      FOR(k, 0, m + 1) a[j][k] = (a[j][k] + p - 1ll * a[i][k] * c % p) % p;
    }
  }
  int ans = 0;
  FOR(i, n, m) {
    ans ^= a[i][m];
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

