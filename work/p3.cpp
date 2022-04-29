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
const int N = 1e5+5, W = 29;
const int p = 998244353;
int n, m;

struct mat {
  int a[N];
  int &operator() (int x, int y) {
    return a[m*(x-1)+y-1];
  }
} a;

int a1,a2,a3,a4;
bool b[N];

inline i64 calc(bool mod = 0) {
  int j = 0;
  i64 ans = 0;
  FOR(i,1,m) {
    if (b[i]) {
      ans += i - j;
    } else j = i;
  }
  if (mod) return 1ll * m * (m + 1) / 2 - ans;
  return ans;
}

inline void solve() {
  rd(n,m);
  if (n <= m) FOR(i,1,n) FOR(j,1,m) rd(a(i,j));
  else {
    swap(n, m);
    FOR(i,1,m) FOR(j,1,n) rd(a(j, i));
  }
  FOR(i,1,n) FOR(j,1,m) {
    a1 = (a1 + 1ll * i * j * (n - i + 1) % p * (m - j + 1) % p * a(i,j)) % p;
  }
  FOR(k,0,W) FOR(i,1,n) {
    FOR(j,1,m) b[j] = (a(i,j)>>k)&1;
    a2 = (a2 + (calc() << k)) % p;
    FOR(j,i+1,n) {
      FOR(s,1,m) b[s] &= (a(j,s)>>k)&1;
      a2 = (a2 + (calc() << k)) % p;
    }
  }
  FOR(k,0,W) FOR(i,1,n) {
    FOR(j,1,m) b[j] = ~(a(i,j)>>k)&1;
    a3 = (a3 + (calc(1) << k)) % p;
    FOR(j,i+1,n) {
      FOR(s,1,m) b[s] &= ~(a(j,s)>>k)&1;
      a3 = (a3 + ((calc(1) << k))) % p;
    }
  }
  FOR(k,0,W) FOR(i,1,n) {
    bitset<N> b;
    bool c = 0;
    FOR(j,1,m) c ^= (a(i,j)>>k)&1, b[j] = c;
    a4 = (a4 + 1ll * b.count() * (m + 1 - b.count()) * (1ll << k)) % p;
    FOR(j,i+1,n) {
      c = 0;
      FOR(s,1,m) c ^= ((a(j,s)>>k)&1), b[s] = b[s] ^ c;
      a4 = (a4 + 1ll * b.count() * (m + 1 - b.count()) * (1ll << k)) % p;
    }
  }
  O(a1,a2,a3,a4);
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

