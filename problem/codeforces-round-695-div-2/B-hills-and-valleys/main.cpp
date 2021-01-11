// Original Author: misaka18931
// Date: 01-08-21
// tag: simulation, *1700
// AC

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 300005
using namespace std;
typedef long long LL;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int a[MX];
int v[MX];
int n;

int calc(int i) {
  int ans = 0;
  int cmp = v[i - 1] + v[i] + v[i + 1];
  for (int j = i - 1; j <= i + 1; ++j) {
    if (j <= 0 || j >= n - 1) continue;
    if (a[j - 1] > a[j] && a[j + 1] > a[j])
      ++ans;
    if (a[j - 1] < a[j] && a[j + 1] < a[j])
      ++ans;
  }
  return (cmp - ans);
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int cnt = 0;
  for (int i = 1; i < n - 1; ++i) {
    if (a[i - 1] > a[i] && a[i + 1] > a[i]) v[i] = 1, ++cnt;
    if (a[i - 1] < a[i] && a[i + 1] < a[i]) v[i] = 1, ++cnt;
  }
  int p = 0;
  for (int i = 1; i < n - 1; ++i) {
    int bak = a[i];
    a[i] = a[i - 1];
    p = max(p, calc(i));
    a[i] = a[i + 1];
    p = max(p, calc(i));
    a[i] = bak;
  }
  cout << cnt - p << endl;
  for (int i = 0; i < n; ++i) {
    a[i] = v[i] = 0;
  }
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}

