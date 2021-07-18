#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
#define MX 105
bool vis[MX][MX][MX];
int rem[MX][MX][MX];

int solve(int n, int m, int k) {
  if (!n && k) return -1e9;
  if (k > n) return -1e9;
  if (vis[n][m][k]) return rem[n][m][k];
  int ret = 0;
  for (int cnt = 0; k * cnt <= n && cnt * (cnt - 1) / 2 <= m; ++cnt) {
    ret = max(ret, cnt + solve(n - k * cnt, m - cnt * (cnt - 1) / 2, k + 1));
  }
  vis[n][m][k] = 1;
  rem[n][m][k] = ret;
  return ret;
}

int main() {
  int n, m;
  cin >> n >> m;
  cout << max(solve(n, m, 0), solve(m, n, 0)) << endl;
  return 0;
}
