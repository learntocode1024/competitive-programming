// Original Author: misaka18931
// Date: 02-05-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LF << '\n'
#define SPC << ' '
#define CLRBUF cout << endl;
#define MX 100005
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;

int head[MX], val[MX], nxt[MX];
int tot;

inline void print(const bool &b) {
  if (b) cout << "YES" << endl;
  else cout << "NO" << endl;
}

inline void add(int x, int col) {
  val[++tot] = x;
  nxt[tot] = head[col];
  head[col] = tot;
}

inline int extract(int col) {
  if (head[col] == 0) return -1;
  int ans = val[head[col]];
  head[col] = nxt[head[col]];
  return ans;
}

int col[MX], w[MX], p[MX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    head[i] = 0;
  }
  tot = 0; // init
  for (int i = 0; i < n; ++i) {
    cin >> col[i];
  }
  for (int i = 0, t; i < n; ++i) {
    cin >> t;
    if (t != col[i]) add(i, t), col[i] = t;
  } // diff
  for (int i = 0; i < m; ++i) {
    cin >> w[i];
  }
  int reg = extract(w[m - 1]);
  if (reg == -1) {
    for (int i = 0; i < n; ++i) {
      if (col[i] == w[m - 1]) {
        reg = i;
        break;
      }
    }
  }
  if (reg == -1) {
    print(0);
    return;
  }
  p[m - 1] = reg;
  for (int i = m - 2; i >= 0; --i) {
    int curr = extract(w[i]);
    if (curr == -1) p[i] = reg;
    else p[i] = curr;
  }
  for (int i = 0; i < n; ++i) {
    if (head[i] > 0) {
      print(0);
      return;
    }
  }
  print(1);
  for (int i = 0; i < m; ++i) {
    cout << p[i] + 1 << ' ';
  }
  CLRBUF
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