#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
#define FOR4(i) FOR(i, 0, 4)
const int N = 1e6+5;
const int p = 1e9+7;
inline void red(int &x) { if (x >= p) x -= p; }

char s[N];
int tran[256];
int dp[N][4][4];

#define T0 \
  red(dp[i][1][0] += dp[i-1][3][1]); \
  red(dp[i][0][0] += dp[i-1][1][0]); \
  red(dp[i][0][0] += dp[i-1][0][0]);  

#define T1 \
  red(dp[i][0][1] += dp[i-1][0][0]); \
  red(dp[i][0][1] += dp[i-1][1][0]); \
  red(dp[i][1][1] += dp[i-1][3][1]); \
  red(dp[i][3][1] += dp[i-1][1][3]); \
  red(dp[i][3][1] += dp[i-1][3][3]); \
  red(dp[i][3][1] += dp[i-1][2][3]);  

#define T2 \
  red(dp[i][3][2] += dp[i-1][1][3]); \
  red(dp[i][3][2] += dp[i-1][3][3]); \
  red(dp[i][3][2] += dp[i-1][2][3]);  

#define T3 \
  red(dp[i][2][3] += dp[i-1][3][2]); \
  red(dp[i][1][3] += dp[i-1][0][1]); \
  red(dp[i][1][3] += dp[i-1][1][1]); \
  red(dp[i][3][3] += dp[i-1][1][3]); \
  red(dp[i][3][3] += dp[i-1][3][3]); \
  red(dp[i][3][3] += dp[i-1][2][3]);  

bool v[4][4];

int main() {
  freopen("mine.in", "r", stdin);
  freopen("mine.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  tran['0'] = 0;
  tran['1'] = 1;
  tran['2'] = 2;
  tran['*'] = 3;
  v[0][0] = 1;
  v[0][1] = 1;
  v[3][1] = 1;
  v[3][2] = 1;
  v[1][3] = 1;
  v[3][3] = 1;
  cin >> s + 1;
  int n = strlen(s + 1);
  if (n < 2) {
    cout << (s[1] == '?' ? 4 : 1) << '\n';
    return 0;
  }
  FOR4(i) FOR4(j) {
    if (s[1] == '?' || tran[s[1]] == i) {
      if (s[2] == '?' || tran[s[2]] == j) {
        if (v[i][j]) dp[2][i][j] = 1;
      }
    }
  }
  for (int i = 3; s[i] != '\0'; ++i) {
    if (s[i] == '?') {
      {T1} {T2} {T3} {T0}
    } else {
      int cur = tran[s[i]];
      if (cur == 0) {T0};
      if (cur == 1) {T1};
      if (cur == 2) {T2};
      if (cur == 3) {T3};
    }
  }
  int ans = 0;
  FOR4(i) FOR4(j) if (v[j][i]) red(ans += dp[n][i][j]);
  cout << ans << '\n';
  return 0;
}
