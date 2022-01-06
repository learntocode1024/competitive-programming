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
const int N = 2<<24;
int n, m, k;
i64 a[N], b[N];
int to[256];
char s[20];

inline void rd_strat(i64 *a, int n) {
  FOR(i, 0, n) {
    cin >> s;
    int u = 0;
    FOR(j, 0, k) {
      u |= to[s[j]] << (j*2);
    }
    ++a[u];
  }
}

inline void conv(i64 *a) {
  FOR(i, 0, k) {
    FOR(u, 0, 1 << (2 * k - 2 * i - 2)) {
      FOR(v, 0, 1 << (2 * i)) {
        FOR(t, 0, 3) a[(u << (2 * i + 2)) | (3 << 2 * i) | v]
          += a[(u << (2 * i + 2)) | (t << 2 * i) | v];
      }
    }
  }
}
inline void iconv(i64 *a) {
  FOR(i, 0, k) {
    FOR(u, 0, 1 << (2 * k - 2 * i - 2)) {
      FOR(v, 0, 1 << (2 * i)) {
        FOR(t, 0, 3) a[(u << (2 * i + 2)) | (3 << 2 * i) | v]
          -= a[(u << (2 * i + 2)) | (t << 2 * i) | v];
      }
    }
  }
}

inline void gans(int i, int u) {
  if (i == k) {
    println(1ll * n * m - a[u]);
    return;
  }
  FOR(j, 0, 3) gans(i+1, u | (j << (i * 2)));
}

inline void solve() {
  rd(k, n, m);
  rd_strat(a, n);
  rd_strat(b, m);
  conv(a);
  conv(b);
  FOR(i, 0, 1 << (k*2)) a[i] *= b[i];
  iconv(a);
  FOR(i, 0, k) {
    FOR(u, 0, 1 << (2 * k - 2 * i - 2)) {
      FOR(v, 0, 1 << (2 * i)) {
        i64 x0 = a[(u << (2 * i + 2)) | (0 << 2 * i) | v];
        i64 x1 = a[(u << (2 * i + 2)) | (1 << 2 * i) | v];
        i64 x2 = a[(u << (2 * i + 2)) | (2 << 2 * i) | v];
        i64 x3 = a[(u << (2 * i + 2)) | (3 << 2 * i) | v];
        a[(u << (2 * i + 2)) | (0 << 2 * i) | v] = x0 + x2 + x3;
        a[(u << (2 * i + 2)) | (1 << 2 * i) | v] = x0 + x1 + x3;
        a[(u << (2 * i + 2)) | (2 << 2 * i) | v] = x1 + x2 + x3;
      }
    }
  }
  gans(0, 0);
}

int main() {
  to['P']=0;
  to['R']=1;
  to['S']=2;
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

