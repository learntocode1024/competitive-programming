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
const int N = 105;
const int p = 998244353;
inline void red(int &x) {
  if (x >= p) x -= p;
}
vector<int> sub[N];
int pw[N];
char s[N];
int cnt[N];
int f[N], g[N];
map<pair<int, u64>, int> mem;

int h(int n, u64 S) {
  if (mem.find({n,S})!=mem.end()) {
    return mem[{n,S}];
  }
  vector<int> f(n+1,0), g(n+1,0);
  g[0] = 1;
  FOR(i, 1, n+1) {
    for (int k = i-1, c = (S>>i)&1; k >= 0; c+=(S>>k)&1,--k) {
      red(f[i] += 1ll * pw[c] * g[k] % p);
    }
    FOR(k, 0, i-1) {
      int cur = 0;
      for (auto m : sub[i-k]) {
        u64 T = 0;
        FOR(r, 0, m) {
          for (int d = k+1+r; d <= i; d += m) {
            if (!((S>>d)&1)) T |= 1ull << r;
          }
        }
        T ^= (1ull << m) - 1;
        red(cur += h(m, T<<1));
      }
      red(g[i] += 1ll * cur * (f[k]+g[k]) % p);
    }
  }
  return mem[{n,S}] = (f[n]+g[n])%p;
}

inline void solve() {
  int n;
  cin >> s+1;
  n = strlen(s+1);
  FOR(i, 1, n + 1) {
    cnt[i] = cnt[i-1] + (s[i] == '1');
  }
  pw[0] = 1;
  FOR(i, 1, n+1) {
    pw[i] = (pw[i-1]<<1)%p;
  }
  FOR(k, 1, N) {
    for (int j = k * 2; j < N; j += k) {
      sub[j].pb(k);
    }
  }
  g[0] = 1;
  FOR(i, 1, n+1) {
    FOR(k, 0, i) {
      red(f[i] += 1ll * pw[cnt[i]-cnt[k]] * g[k] % p);
    }
    FOR(k, 0, i-1) {
      int cur = 0;
      for (auto m : sub[i-k]) {
        u64 S = 0;
        FOR(r, 0, m) {
          for (int d = k+1+r; d <= i; d += m) {
            if (s[d] == '0') S |= 1ull << r;
          }
        }
        S ^= (1ull << m) - 1;
        red(cur += h(m, S<<1));
      }
      red(g[i] += 1ll * cur * (f[k]+g[k]) % p);
    }
  }
  println((f[n]+g[n])%p);
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

