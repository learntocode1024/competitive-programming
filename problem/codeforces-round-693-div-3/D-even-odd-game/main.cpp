// Original Author: misaka18931
// Date: 01-04-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#define MX
using std::cin;
using std::cout;
using std::endl;
using std::memset;
typedef long long LL;

std::priority_queue<LL> e, o;

void solve() {
  o = e = std::priority_queue<LL>();
  int n;
  cin >> n;
  LL a;
  for (int i = 0; i < n; ++i) {
    cin >> a;
    if (a & 1) o.push(a);
    else e.push(a);
  }
  LL ans = 0;
  for (int i = 0; i < n; ++i) {
    if (i & 1) {
      if (o.empty()) {
        e.pop();
      } else if (e.empty()) {
        ans += o.top();
        o.pop();
      } else {
        if (o.top() > e.top()) {
          ans += o.top();
          o.pop();
        } else {
          e.pop();
        }
      }
    } else { // bob
      if (o.empty()) {
        ans -= e.top();
        e.pop();
      } else if (e.empty()) {
        o.pop();
      } else {
        if (o.top() > e.top()) {
          o.pop();
        } else {
          ans -= e.top();
          e.pop();
        }
      }
    } // alice
  }
  if (ans > 0) cout << "Bob\n";
  if (ans == 0) cout << "Tie\n";
  if (ans < 0) cout << "Alice\n";
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
