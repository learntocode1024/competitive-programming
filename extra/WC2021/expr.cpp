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
const int N = 5e4+5, M = 10;
const int p = 1e9+7;
int n, m, rt;
int a[N][M];
int dp[N][1<<M][2];
int ch[N][2];
int op[N];
char s[N];
int tot;

void dfs(int u) {
  if (!ch[u][0]) {
    FOR(i, 0, 1<<m) {
      dp[u][i][(i>>op[u])&1] = 1;
    }
    return;
  }
  const int &l = ch[u][0], &r = ch[u][1];
  dfs(l);
  dfs(r);
  if (op[u] & 1) { // and
    FOR(i, 0, 1 << m) {
      dp[u][i][0] = (1ll*dp[l][i][0]*dp[r][i][0]+1ll*dp[l][i][1]*dp[r][i][0]+1ll*dp[l][i][0]*dp[r][i][1])%p;
      dp[u][i][1] = 1ll*dp[l][i][1]*dp[r][i][1]%p;
    }
  }
  if (op[u] & 2) { // or
    FOR(i, 0, 1 << m) {
      dp[u][i][0] = (dp[u][i][0]+1ll*dp[l][i][0]*dp[r][i][0])%p;
      dp[u][i][1] = (dp[u][i][1]+1ll*dp[l][i][1]*dp[r][i][0]+1ll*dp[l][i][0]*dp[r][i][1]+1ll*dp[l][i][1]*dp[r][i][1])%p;
    }
  }
}

int build(int &i) {
  int lhs, rhs, opr;
  if (s[i] == '(') {
    ++i;
    lhs = build(i);
  } else {
    op[++tot] = s[i++] - '0';
    lhs = tot;
  }
  for (;s[i] != ')'; ++i) {
    if (s[i] == '<') opr = 1;
    else if (s[i] == '>') opr = 2;
    else if (s[i] == '?') opr = 3;
    else { // read rhs
      if (s[i] == '(') {
        ++i;
        rhs = build(i);
      } else {
        op[++tot] = s[i] - '0';
        rhs = tot;
      }
      op[++tot] = opr;
      ch[tot][0] = lhs;
      ch[tot][1] = rhs;
      lhs = tot;
    }
  }
  return lhs;
}

pii b[M];

inline void solve() {
  cin >> n >> m;
  FOR(i, 0, m) FOR(j, 0, n) cin >> a[j][i];
  int iter = 1;
  cin >> s + 1;
  int ll = strlen(s + 1);
  s[1+ll] = ')';
  rt = build(iter);
  dfs(rt);
  int ans = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) b[j] = mkp(a[i][j], j);
    sort(b, b + m);
    int u = (1<<m)-1;
    ans = (ans + 1ll * b[0].fi * dp[rt][u][1]) % p;
    FOR(j, 1, m) {
      u ^= 1 << b[j-1].se;
      ans = (ans + 1ll * (b[j].fi-b[j-1].fi) * dp[rt][u][1]) % p;
    }
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

