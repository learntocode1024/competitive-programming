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

const int N = 120, S = 26*2, S2 = S * 2;
int g[N][N];
char s[15][N];
int n;
bool vis[N];
inline int get(char ch) {
  int ret;
  if (isupper(ch)) ret = ch - 'A';
  else ret = ch - 'a' + 26;
  ++ret;
  if (vis[ret]) ret += S;
  vis[ret] = 1;
  return ret;
}

inline char teg(int x) {
  if (x > S) x -= S;
  --x;
  if (x < 26) return 'A' + x;
  x -= 26;
  return 'a' + x;
}

int t[15][N];
int cnt[N];
int dp[N], pr[N];
char ans[N];

inline void solve() {
  FOR(i, 1, S2+1) FOR(j, 1, S2+1) g[i][j] = 0;
  cin >> n;
  FOR(i, 0, n) cin >> s[i];
  int len1;
  int len = len1 = strlen(s[0]);
  FOR(j, 0, S2+1) vis[j] = 0, cnt[j] = 0;
  FOR(i, 0, len) t[0][i] = get(s[0][i]), s[0][i] = '\0', ++cnt[t[0][i]];
  FOR(i, 0, len) FOR(j, i + 1, len) {
    ++g[t[0][i]][t[0][j]];
  }
  FOR(i, 1, n) {
    len = strlen(s[i]);
    FOR(j, 0, S2+1) vis[j] = 0;
    FOR(j, 0, len) t[i][j] = get(s[i][j]), s[i][j] = '\0', ++cnt[t[i][j]];
    FOR(j, 0, len) FOR(k, j + 1, len) {
      ++g[t[i][j]][t[i][k]];
    }
  }
  FOR(i, 0, S2+1) dp[i] = pr[i] = 0;
  int mx = 0;
  FOR(i, 0, len1) {
    int u = t[0][i];
    if (cnt[u] != n) continue;
    dp[u] = 1;
    FOR(j, 0, i) {
      int pre = t[0][j];
      if (g[pre][u] == n) {
        if (dp[pre] + 1 > dp[u]) {
          dp[u] = dp[pre] + 1;
          pr[u] = pre;
        }
      }
    }
    if (dp[u] > dp[mx]) mx = u;
  }
  cout << dp[mx] << '\n';
  int tot = 0;
  while (mx) {
    ans[++tot] = teg(mx);
    mx = pr[mx];
  }
  while (tot) cout << ans[tot--];
  cout << '\n';
}

int main() {
#ifndef MISAKA
  //freopen(".in", "r", stdin);
  //freopen(".out", "w", stdout);
  // ios::sync_with_stdio(0);
  // cin.tie(0);
#endif
  int T;
  cin >> T;
  while (T--)
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

