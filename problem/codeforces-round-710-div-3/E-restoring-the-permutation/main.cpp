// Original Author: misaka18931
// Date: 03-18-21
// tag:
// 

#include <cstdio>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define MX 200005

int a[MX], mina[MX], maxa[MX];
bool vis[MX];
queue<int> q;
stack<int> s;

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) a[i] = vis[i] = 0;
  for (int i = 0, curr, prev = 0; i < n; ++i) {
    cin >> curr;
    if (curr == prev) continue;
    mina[i] = maxa[i] = a[i] = curr;
    vis[curr] = true;
    prev = curr;
  }
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) q.push(i);
  for (int i = 0; i < n; ++i) {
    if (!a[i]) mina[i] = q.front(), q.pop();
  }
  int pre = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i]) {
      for (int j = pre + 1; j < a[i]; ++j) {
        s.push(j);
      }
      pre = a[i];
    } else {
      maxa[i] = s.top();
      s.pop();
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << mina[i] << ' ';
  }
  cout << endl;
  for (int i = 0; i < n; ++i) {
    cout << maxa[i] << ' ';
  }
  cout << endl;
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
