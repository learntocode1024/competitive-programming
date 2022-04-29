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
char s[N];
int typ[N];
int c[4];
map<char,int> mp = {{'R',0},{'G',1},{'B',2}};

inline void solve() {
  int n;
  rd(n);
  cin >> s + 1;
  FOR(i,1,n*3) typ[i] = 2;
  FOR(i,1,n*3) {
    ++c[mp[s[i]]];
    int cnt = 0;
    FOR(i,0,2) cnt += c[i] != 0;
    if (cnt == 3) {
      FOR(i,0,2) c[i]--;
      typ[i] = 3;
    }
  }
  FOR(i,0,3) c[i] = 0;
  ROF(i,1,n*3) {
    ++c[mp[s[i]]];
    int cnt = 0;
    FOR(i,0,2) cnt += c[i] != 0;
    if (cnt == 3) {
      FOR(i,0,2) c[i]--;
      typ[i] = 1;
    }
  }
  FOR(i,0,3) c[i] = 0;
  int ans = 1;
  FOR(i,2,n) ans = 1ll * ans * i % p;
  FOR(i,1,n*3) {
    if (typ[i] == 1)++c[typ[i]];
    if (typ[i] == 2) {
      ans = 1ll * ans * (c[1]--) % p;
    }
  }
  FOR(i,0,3) c[i] = 0;
  ROF(i,1,n*3) {
    ++c[typ[i]];
    if (typ[i] == 2) {
      ans = 1ll * ans * (c[3]--) % p;
    }
  }
  O(ans);
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

