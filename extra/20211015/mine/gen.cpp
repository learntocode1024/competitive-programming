#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
const int N = 14;
int n = 10;
bool vis[N];
int a[N];
char s[N];
int ans = 0;
const char* to = "012*";

inline bool chk() {
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '0' && (s[i - 1] == '*' || s[i + 1] == '*')) return 0; 
    if (s[i] == '1' && !((s[i - 1] == '*') ^ (s[i + 1] == '*'))) return 0; 
    if (s[i] == '2' && !(s[i - 1] == '*' && s[i + 1] == '*')) return 0; 
    if (s[i] == '*' && (s[i - 1] == '0' || s[i + 1] == '0')) return 0; 
  }
  return 1;
}

void dfs(int k) {
  if (k == n + 1) {
    ans += chk();
    return;
  }
  if (s[k] == '?') {
    for (int i = 0; i < 4; ++i) {
      s[k] = to[i];
      dfs(k + 1);
    }
    s[k] = '?';
  } else {
    dfs(k + 1);
  }
}

int main() {
  FOR(i, 1, n + 1) s[i] = '?';
  i64 seed = chrono::steady_clock::now().time_since_epoch().count();
  mt19937 gen(seed);
  uniform_int_distribution<int> e{1, n};
  uniform_int_distribution<int> f{0, 3};
  int all = e(gen);
  for (int i = 0; i < all; ++i) {
    s[e(gen)] = to[f(gen)];
  }
  cout << s + 1 << '\n';
  dfs(1);
  cerr << ans << '\n';
  return 0;
}
