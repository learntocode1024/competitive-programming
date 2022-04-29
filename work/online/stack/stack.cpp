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
const int N = 5e5+5;
int L[N];
int a[N], b[N], s[N], tl;
vector<pii> q[N];
int ans[N];
int c[N];
void ins(int x, int v) {
  for (; x < N; x += x & -x) c[x] += v;
}

int get(int x) {
  int ret = 0;
  for (; x; x -= x & -x) ret += c[x];
  return ret;
}

inline void solve() {
  int n, Q;
  rd(n, Q);
  FOR(i,1,n) rd(a[i]);
  FOR(i,1,n) rd(b[i]);
  FOR(i,1,n) {
    while (tl && (a[s[tl]] == a[i] || b[s[tl]] <= b[i])) --tl;
    L[i] = s[tl] + 1;
    s[++tl] = i;
  }
  FOR(i,1,Q) {
    int l, r;
    rd(l,r);
    q[r].eb(l, i);
  }
  FOR(i,1,n) {
    ins(L[i], 1);
    ins(i+1, -1);
    for (auto l : q[i]) {
      ans[l.se] = get(l.fi);
    }
  }
  FOR(i,1,Q) O(ans[i]);
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

